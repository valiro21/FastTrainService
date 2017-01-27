//
// Created by vrosca on 1/26/17.
//

#include "ShortestPathProvider.hpp"
#include <queue>
#include <unordered_map>
#include <Calendar.hpp>
#include <future>

std::vector<std::pair<int, std::pair< std::pair<long long,  std::string>, std::pair<float, int> > > > getNeighbours (int id, Calendar c, float lat, float lng) {
    std::string str_lng = std::to_string(lng);
    std::string str_lat = std::to_string(lat);
    std::string query = "MATCH (a:Stop{id: '" + std::to_string(id) + "'})-[t1:TO_TRIP]->(tr:Trip)-[t2:TO_STOP]->(b:Stop), " +
            "(tr)-[:HAS]->(s:Service) " +
            "WHERE t1.nr < t2.nr RETURN b.id, b.lat, b.lng, t1.departure, t2.arrival, s, tr.id, size((b)-->())";

    std::vector<std::pair<int, std::pair<std::pair<long long,  std::string>, std::pair<float, int> > > > vresult;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        while (result != NULL) {
            std::string idn_str = DatabaseUtils::GetInstance().neo4j_get_string(neo4j_result_field(result, 0));
            std::string lat_str = DatabaseUtils::GetInstance().neo4j_get_string(neo4j_result_field(result, 1));
            std::string lng_str = DatabaseUtils::GetInstance().neo4j_get_string(neo4j_result_field(result, 2));
            int departure = (int) neo4j_int_value(neo4j_result_field(result, 3));
            int arrival = (int) neo4j_int_value(neo4j_result_field(result, 4));
            json service = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 5))["properties"];
            std::string trip_id  = DatabaseUtils::GetInstance().neo4j_get_string(neo4j_result_field(result, 6));
            int rels = (int) neo4j_int_value(neo4j_result_field(result, 7));

            int idn = std::stoi(idn_str);
            if (idn == 11906)
                idn = 11906;
            float tlat = std::stof(lat_str);
            float tlng = std::stof(lng_str);
            float dist = (lat - tlat) * (lat - tlat) + (lng - tlng) * (lng - tlng);

            long long time = arrival - departure;

            if (c.getDayTimeUnix() < departure && service[c.getDayName()].get<std::string>() == "1") {
                time += departure - c.getDayTimeUnix();
            }
            else {
                Calendar c2 = c;
                c2.set(23, Calendar::HOUR);
                c2.set(59, Calendar::MINUTE);
                c2.set(59, Calendar::SECOND);
                time += c2.getDayTimeUnix() - c.getDayTimeUnix() + 1;
                c2.add(1, Calendar::SECOND);

                int day = 0;
                while (day < 3 && service[c2.getDayName()].get<std::string>() != "1") {
                    time += 24 * 60 * 60;
                    c2.add(1, Calendar::DAY);
                    day++;
                }
                if (day == 3) {
                    result = neo4j_fetch_next(result_stream);
                    continue;
                }
            }

            vresult.push_back(std::make_pair (idn, std::make_pair(std::make_pair(time, trip_id), std::make_pair(dist, rels))));
            result = neo4j_fetch_next(result_stream);
        }
    });
    return vresult;
};

void createResult (int node,
                   std::vector<json> & result,
                   std::unordered_map<int, std::pair<int, std::string> > &prev,
                   std::unordered_map<int, long long> &road
) {
    auto it = prev.find(node);
    if ( it == prev.end ()) {
        return;
    }

    createResult(it->second.first, result, prev, road);

    json path;
    path["start"] = DatabaseUtils::GetInstance().getStopById (it->second.first);
    long long departure = DatabaseUtils::GetInstance().getDepartureByStopAndTrip (it->second.first, it->second.second);
    long long arrival = DatabaseUtils::GetInstance().getArrivalByStopAndTrip (node, it->second.second);
    long long time = arrival - departure;

    path["duration"] = time;
    path["route"] = DatabaseUtils::GetInstance().getRouteByTripId (it->second.second);
    path["arrival"] = road[node];
    path["end"] = DatabaseUtils::GetInstance().getStopById (node);
    result.push_back(path);
}

json ShortestPathProvider::provide(json request) {
    std::string origin = request["origin"];
    std::string destination = request["destination"];
    Calendar time = Calendar::fromJSON(request["time"]);

    std::priority_queue<std::pair<std::pair<float, long long>, int>, std::vector<std::pair<std::pair<float, long long>, int> >, std::greater<std::pair<std::pair<float, long long>, int> > > q;
    std::unordered_map<int, long long> road;
    std::unordered_map<int, std::pair<int,  std::string> > prev;

    int origin_id = DatabaseUtils::GetInstance().getId (origin);
    int final_id = DatabaseUtils::GetInstance().getId (destination);

    if (origin_id == -1 || final_id == -1) {
        json result;
        result["ERROR"] = "City not found";
        return result;
    }

    json origin_stop = DatabaseUtils::GetInstance().getStopById(origin_id);
    json final_stop = DatabaseUtils::GetInstance().getStopById(final_id);
    float olat = std::stof(origin_stop["lat"].get<std::string>());
    float olng = std::stof(origin_stop["lng"].get<std::string>());

    float lat = std::stof(final_stop["lat"].get<std::string>());
    float lng = std::stof(final_stop["lng"].get<std::string>());

    float max_dist = (lat - olat) * (lat - olat) + (lng - olng) * (lng - olng);

    road[origin_id] = 0;
    q.push (std::make_pair (std::make_pair (0, 0), origin_id));
    while (!q.empty ()) {
        auto nod = q.top ();
        q.pop();
        if (nod.second == final_id) break;

        if (road[nod.second] < nod.first.second) continue;

        Calendar c = time;
        c.add((int) nod.first.second, Calendar::SECOND);
        auto ngh = getNeighbours(nod.second, c, lat, lng);

        bool stop = false;
        for (auto it : ngh) {
            long long &n = road[it.first];
            if (nod.first.second + it.second.first.first < n || n == 0 && it.first != origin_id) {
                n = nod.first.second + it.second.first.first;

                float score = it.second.second.first;
                score /= max_dist;
                score += (float) 100 / (float)it.second.second.second;

                q.push (std::make_pair(std::make_pair (score, n), it.first));
                prev[it.first] = std::make_pair(nod.second, it.second.first.second);
                if (it.first == final_id)
                    stop = true;
            }

            if (stop) {
                std::vector<json> result;
                createResult (final_id, result, prev, road);
                json totals = json (result);
                return totals;
            }
        }
    }

    if (prev.find(final_id) == prev.end ()) {
        json result;
        result["ERROR"] = "No path between cities";
        return result;
    }

    std::vector<json> result;
    createResult (final_id, result, prev, road);
    json totals = json (result);
    return totals;
}