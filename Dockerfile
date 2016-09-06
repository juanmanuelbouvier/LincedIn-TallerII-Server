FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y git curl g++ make cmake valgrind doxygen graphviz python3-setuptools
RUN easy_install3 pip

WORKDIR /root/LincedIn/LincedIn-TallerII-Server
COPY . .
RUN make

EXPOSE 8080

WORKDIR /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/
CMD ["sh", "-c", "/root/LincedIn/LincedIn-TallerII-Server/config/build/bin/LincedInAppServer"]
