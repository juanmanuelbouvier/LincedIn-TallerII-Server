FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y git g++ make cmake doxygen graphviz python3-setuptools
RUN easy_install3 pip

RUN mkdir /root/LincedIn && cd /root/LincedIn/ && git clone https://github.com/juanmanuelbouvier/LincedIn-TallerII-Server.git && cd LincedIn-TallerII-Server && make

CMD /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/LincedInServer
