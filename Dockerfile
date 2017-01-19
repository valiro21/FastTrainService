FROM ubuntu:latest
MAINTAINER Valentin Rosca<rosca.valentin2012@gmail.com>
ARG CMAKE_VERSION=3.7.1
RUN apt-get update
RUN apt-get -y install software-properties-common
RUN apt-get -y install g++ make wget
RUN add-apt-repository ppa:cleishm/neo4j && apt-get update && apt-get -y install libssl-dev neo4j-client libneo4j-client-dev
RUN apt-get -y install qt5-default qtlocation5-dev libqt5location5-plugins
RUN wget https://cmake.org/files/v3.7/cmake-${CMAKE_VERSION}.tar.gz && \
					tar -xvaf cmake-*.tar.gz && \
					cd cmake-* && \
					./bootstrap && \
					make && \
					make install
RUN ln -s /usr/bin/make /usr/bin/gmake
RUN ln -s /usr/bin/cc /usr/local/bin/cc
RUN ln -s /usr/bin/g++ /usr/local/bin/g++
COPY ./ /FastTrainService
RUN cd /FastTrainService && cmake -DCMAKE_BUILD_TYPE=Release ./ && make
RUN cp /FastTrainService/bin/Release/FastTrainServer ./
EXPOSE 8181
CMD /FastTrainService
