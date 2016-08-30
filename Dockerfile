FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y git g++ make cmake doxygen graphviz python3-setuptools
RUN easy_install3 pip

WORKDIR /root/LincedIn/
RUN git clone https://github.com/juanmanuelbouvier/LincedIn-TallerII-Server.git
WORKDIR /root/LincedIn/LincedIn-TallerII-Server
RUN make

WORKDIR /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/
CMD ["sh", "-c", "/root/LincedIn/LincedIn-TallerII-Server/config/build/bin/LincedInServer ; /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/RunUnitTests"]
