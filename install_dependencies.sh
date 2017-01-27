apt-get update && \
apt-get -y install software-properties-common && \
apt-get -y install g++ make wget cmake && \
add-apt-repository ppa:cleishm/neo4j && apt-get update && apt-get -y install libssl-dev neo4j-client libneo4j-client-dev && \
apt-get -y install qt5-default qtlocation5-dev libqt5location5-plugins