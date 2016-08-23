FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y cmake doxygen graphviz python3-setuptools
RUN easy_install3 pip

RUN apt-get install -y git
RUN mkdir /home/LincedIn-AppServer
RUN cd /home/LincedIn-AppServer/
RUN git clone https://github.com/juanmanuelbouvier/LincedIn-TallerII-Server.git

CMD make
