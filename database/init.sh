#!/bin/bash
# Fix issue with volume on data - Copy db to data on first initialisation

if [ ! -d "/data/databases" ] || [ ! -d "/data/databases/graph.db" ]; then
  echo -n "Initialising ... "
  mkdir -p /data/databases/graph.db
  cp -r /trains.db/* /data/databases/graph.db
  echo "DONE"
fi

/docker-entrypoint.sh $@
