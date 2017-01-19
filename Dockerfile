FROM valiro21/fasttrainservice-build-environment:latest
MAINTAINER Valentin Rosca<rosca.valentin2012@gmail.com>
COPY ./ /FastTrainService
RUN cd /FastTrainService && cmake -DCMAKE_BUILD_TYPE=Release ./ && make
RUN cp /FastTrainService/bin/Release/FastTrainServer ./
EXPOSE 8181
CMD /FastTrainServer
