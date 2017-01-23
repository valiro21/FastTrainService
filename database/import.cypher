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
LOAD CSV WITH HEADERS FROM "file:/tmp/data/trips.txt" AS row
CREATE(train:Train{
  id: row.trip_id,
  ShortName: row.trip_short_name
})
WITH train, row
MATCH (route:Route{id: row.route_id})
MERGE (train)-[:HAS]->(route);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stop_times.txt" AS row
MATCH (train:Train{id: row.trip_id}), (stop:Stop{id:row.stop_id})
WHERE row.arrival_time is not null
MERGE (train)-[:TO_STOP{arrival:row.arrival_time}]->(stop);

USING PERIODIC COMMIT
LOAD CSV WITH HEADERS FROM "file:/tmp/data/stop_times.txt" AS row
MATCH (train:Train{id: row.trip_id}), (stop:Stop{id:row.stop_id})
WHERE row.departure_time is not null
MERGE (stop)-[:TO_TRAIN{departure:row.departure_time}]->(train);