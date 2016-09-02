FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y git g++ make cmake valgrind doxygen graphviz python3-setuptools
RUN easy_install3 pip

WORKDIR /root/LincedIn/LincedIn-TallerII-Server
COPY . .
RUN make

WORKDIR /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/
CMD ["sh", "-c", "/root/LincedIn/LincedIn-TallerII-Server/config/build/bin/LincedInAppServer ; /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/RunUnitTests"]
