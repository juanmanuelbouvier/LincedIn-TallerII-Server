FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y git curl g++ make cmake valgrind doxygen graphviz python3-setuptools libsnappy-dev libleveldb-dev lcov
RUN easy_install3 pip

WORKDIR /root/LincedIn/LincedIn-TallerII-Server
COPY . .
RUN make build
RUN make test

EXPOSE 8081

CMD ["sh", "-c", "/root/LincedIn/LincedIn-TallerII-Server/config/build/bin/LincedInAppServer"]
