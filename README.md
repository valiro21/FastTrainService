# FastTrainService
A C++ application for managing train arrivals, departures and routes

[![Code Climate](https://codeclimate.com/github/valiro21/FastTrainService/badges/gpa.svg "Codeclimate")](https://codeclimate.com/github/valiro21/FastTrainService)
[![Issue Count](https://codeclimate.com/github/valiro21/FastTrainService/badges/issue_count.svg "Codeclimate")](https://codeclimate.com/github/valiro21/FastTrainService)
[![Docker Pulls](https://img.shields.io/docker/pulls/valiro21/fasttrainservice.svg "Docker Repository")](https://hub.docker.com/r/valiro21/fasttrainservice/)
[![Docker Build](https://img.shields.io/docker/automated/valiro21/fasttrainservice.svg "Docker Hub automated build")](https://hub.docker.com/r/valiro21/fasttrainservice/builds/)
[![license](https://img.shields.io/github/license/valiro21/fasttrainservice.svg "Github license")](LICENSE.MD)
[![Docker Repository on Quay](https://quay.io/repository/valiro21/fasttrainserver/status "Docker Repository for Server on Quay")](https://quay.io/repository/valiro21/fasttrainserver)
[![Docker Repository on Quay](https://quay.io/repository/valiro21/fasttraindatabase/status "Docker Repository for Database on Quay")](https://quay.io/repository/valiro21/fasttraindatabase)


## SetUp

### Variant One - Classic
For building the project, you will need the following packages to be installed:
```$xslt
libssl-dev neo4j-client libneo4j-client-dev qt5-default qtlocation5-dev libqt5location5-plugins
```

Install on Ubuntu with:
```$xslt
apt-get update && \
apt-get -y install software-properties-common && \
apt-get -y install g++ make wget cmake && \
add-apt-repository ppa:cleishm/neo4j && apt-get update && apt-get -y install libssl-dev neo4j-client libneo4j-client-dev && \
apt-get -y install qt5-default qtlocation5-dev libqt5location5-plugins
```

For the build step:
```$xslt
cmake -DCMAKE_BUILD_TYPE=RELEASE ./ && make
```
The RELEASE binalires should be in:
 * Server/bin/RELEASE/FastTrainServer
 * Client/bin/RELEASE/FastTrainClient
 
Before running the server we should setup the database first.

The database is available with docker. If you don't have docker installed then to install docker use:
```$xslt
curl -sSL get.docker.com | sudo sh
```
You may need to login and logout for the changes to take effect.

To run the database use:
```$xslt
docker run -d -p 127.0.0.1:7474:7474 -p 127.0.0.1:7687:7687 --name train_db quay.io/valiro21/fasttraindatabase
```

To run the server, from the root directory, use:
```$xslt
./Server/bin/RELEASE/FastTrainServer
```

After running the server, to run the client, from the root directory, use:
```$xslt
./Client/bin/RELEASE/FastTrainClient
```

### Variant 2 - Docker
Download the latest docker-compose from the github repo master branch valiro21/FastTrainService.

In the folder where you downloaded the above file use:
```$xslt
docker-compose up -d
```

## Versioning ##
We use git as versioning system and GitHub for releases, if any.

# Thanks for reading! Enjoy #