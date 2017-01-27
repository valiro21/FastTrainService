USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/agency.txt" AS row
CREATE (:Agency {
  name: row.agency_name,
  id: row.agency_id,
  url: row.agency_url,
  timezone: row.agency_timezone});

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stops.txt" AS row
CREATE (:Stop {
  name: row.stop_name,
  id: row.stop_id,
  country: "Romania",
  lat: row.stop_lat,
  lng: row.stop_lon});

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/routes.txt" AS row
CREATE(route:Route {
  ShortName: row.route_short_name,
  LongName: row.route_long_name,
  id: row.route_id,
  type: row.route_type
})
WITH route, row
MATCH (agency:Agency{id: row.agency_id})
MERGE (route)-[:BELONGS_TO]->(agency);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/calendar.txt" AS row
CREATE(service:Service{
  id: row.service_id,
  monday: row.monday,
  tuesday: row.tuesday,
  wednesday: row.wednesday,
  thursday: row.thursday,
  friday: row.friday,
  saturday: row.saturday,
  sunday: row.sunday,
  start: row.start_date,
  end: row.end_date
});

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/trips.txt" AS row
CREATE(trip:Trip{
  id: row.trip_id,
  ShortName: row.trip_short_name,
  delay: 0
})
WITH trip, row
MATCH (route:Route{id: row.route_id})
MERGE (trip)-[:FOR]->(route)
WITH trip, row
MATCH (service:Service{id: row.service_id})
MERGE (trip)-[:HAS]->(service);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stop_times.txt" AS row
MATCH (trip:Trip{id: row.trip_id}), (stop:Stop{id:row.stop_id})
WHERE row.arrival_time is not null
MERGE (trip)-[:TO_STOP{
nr: row.stop_sequence,
arrival: toInteger(substring(row.arrival_time,0,2)) * 60 * 60 + toInteger(substring(row.arrival_time, 3, 2)) * 60 + toInteger (substring(row.arrival_time, 6, 2))
}]->(stop);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stop_times.txt" AS row
MATCH (trip:Trip{id: row.trip_id}), (stop:Stop{id:row.stop_id})
WHERE row.departure_time is not null
MERGE (stop)-[:TO_TRIP{
nr: row.stop_sequence,
departure: toInteger(substring(row.departure_time,0,2)) * 60 * 60 + toInteger(substring(row.departure_time, 3, 2)) * 60 + toInteger (substring(row.departure_time, 6, 2))
}]->(trip);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stop_times.txt" AS row
MATCH (trip:Trip{id: row.trip_id})-[:FOR]->(route:Route), (stop:Stop{id:row.stop_id})
WHERE row.arrival_time is null
MERGE (route)-[:STARTS_AT]->(stop);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stop_times.txt" AS row
MATCH (trip:Trip{id: row.trip_id})-[:FOR]->(route:Route), (stop:Stop{id:row.stop_id})
WHERE row.departure_time is null
MERGE (route)-[:ENDS_AT]->(stop);

CREATE CONSTRAINT ON (a:Stop) ASSERT a.name IS UNIQUE;
CREATE CONSTRAINT ON (r:Route) ASSERT r.name IS UNIQUE;
CREATE CONSTRAINT ON (r:Route) ASSERT r.id IS UNIQUE;
CREATE CONSTRAINT ON (a:Stop) ASSERT a.id IS UNIQUE;
CREATE CONSTRAINT ON (t:Trip) ASSERT t.id IS UNIQUE;
CREATE CONSTRAINT ON (s:Service) ASSERT s.id IS UNIQUE;
