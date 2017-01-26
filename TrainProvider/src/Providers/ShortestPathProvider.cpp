//
// Created by vrosca on 1/26/17.
//

#include "ShortestPathProvider.hpp"
#include <queue>
#include <unordered_map>
#include <Calendar.hpp>
#include <future>

std::vector<std::pair<int, std::pair< std::pair<long long,  std::string>, float > > > getNeighbours (int id, Calendar c, float lat, float lng) {
    std::string str_lng = std::to_string(lng);
    std::string str_lat = std::to_string(lat);
    std::string query = "MATCH (a:Stop{id: '" + std::to_string(id) + "'})-[t1:TO_TRIP]->(tr:Trip)-[t2:TO_STOP]->(b:Stop), " +
            "(tr)-[:HAS]->(s:Service) " +
            "WHERE t1.nr < t2.nr RETURN b.id, b.lat, b.lng, t1.departure, t2.arrival, s, tr.id "
            + "ORDER BY (toFloat(" + str_lng + ") - toFloat(a.lng))^2 + (toFloat(" + str_lat + ") - toFloat(a.lat))^2 asc";

    std::vector<std::pair<int, std::pair<std::pair<long long,  std::string>, float > > > vresult;
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

            int idn = std::stoi(idn_str);
            if (idn == 11906)
                idn = 11906;
            float tlat = std::stof(lat_str);
            float tlng = std::stof(lng_str);
            float dist = (lat - tlat) * (lat - tlat) + (lng - tlng) * (lng - tlng);

            long long time = arrival - departure;
            if (time < 0) {
                time = 60 * 60 * 24 - departure + arrival;
            }

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

            vresult.push_back(std::make_pair (idn, std::make_pair(std::make_pair(time, trip_id), dist)));
            result = neo4j_fetch_next(result_stream);
        }
    });
    return vresult;
};

int getId (std::string name) {
    std::string query = "MATCH (a:Stop{name: '" + name +"'}) RETURN a;";
    int id;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        while (result != NULL) {
            json station = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];

            id = std::stoi(station["id"].get<std::string>());
            return;
        }
        id = -1;
    });
    return id;
}

json getStopById (int id) {
    std::string query = "MATCH (a:Stop{id: '" + std::to_string(id) +"'}) RETURN a;";
    json stop;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            stop = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        }
        else {
            stop = json();
        }
    });
    return stop;
}

json getRouteByTripId (std::string id) {
    Logger::GetInstance().logd(id);
    std::string query = "MATCH (tr:Trip{id: '" + id +"'})-[:FOR]->(r:Route) RETURN r;";
    json route;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            route = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        }
        else {
            route = json();
        }
    });
    return route;
}

int getDepartureByStopAndTrip (int id, std::string trip_id) {
    std::string query = "MATCH (a:Stop{id: '" + std::to_string(id) + "'})-[t:TO_TRIP]->(tr:Trip{id: '" + trip_id +"'}) RETURN t;";
    int departure;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            json to_trip = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
            departure = to_trip["departure"];
        }
        else {
            departure = -1;
        }
    });
    return departure;
}

int getArrivalByStopAndTrip (int id, std::string trip_id) {
    std::string query = "MATCH (tr:Trip{id: '" + trip_id +"'})-[t:TO_STOP]->(a:Stop{id: '" + std::to_string(id) + "'}) RETURN t;";
    int arrival;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            json to_stop = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
            arrival = to_stop["arrival"];
        }
        else {
            arrival = -1;
        }
    });
    return arrival;
}

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
    path["start"] = getStopById (it->second.first);
    long long departure = getDepartureByStopAndTrip (it->second.first, it->second.second);
    long long arrival = getArrivalByStopAndTrip (node, it->second.second);
    long long time = arrival - departure;
    if (arrival < departure) {
        time = 60 * 60 * 24 - departure + arrival;
    }


    path["duration"] = time;
    path["route"] = getRouteByTripId (it->second.second);
    path["arrival"] = road[node];
    path["end"] = getStopById (node);
    result.push_back(path);
}

json ShortestPathProvider::provide(json request) {
    std::string origin = request["origin"];
    std::string destination = request["destination"];
    Calendar time = Calendar::fromJSON(request["time"]);

    std::priority_queue<std::pair<std::pair<float, long long>, int>, std::vector<std::pair<std::pair<float, long long>, int> >, std::greater<std::pair<std::pair<float, long long>, int> > > q;
    std::unordered_map<int, long long> road;
    std::unordered_map<int, std::pair<int,  std::string> > prev;

    int origin_id = getId (origin);
    int final_id = getId (destination);

    if (origin_id == -1 || final_id == -1) {
        json result;
        result["ERROR"] = "City not found";
        return result;
    }

    json origin_stop = getStopById(origin_id);
    json final_stop = getStopById(final_id);
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

                float score = it.second.second;
                score /= max_dist;
                score += (float)(n) / (float)1000000;

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