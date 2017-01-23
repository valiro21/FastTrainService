FROM neo4j:latest
COPY data /tmp/data
COPY import.cypher /tmp
ENV NEO4J_AUTH=neo4j/train12345
RUN ./bin/neo4j-shell -path /trains.db -file /tmp/import.cypher
COPY init.sh /init.sh
RUN chmod +x /init.sh
ENTRYPOINT ["/init.sh"]
CMD ["neo4j"]
