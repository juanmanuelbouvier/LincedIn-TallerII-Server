FROM ubuntu

RUN apt-get -y update
RUN apt-get install -y git g++ make cmake valgrind doxygen graphviz python3-setuptools
RUN easy_install3 pip

WORKDIR /root/LincedIn/LincedIn-TallerII-Server
COPY . .
RUN make

#TODO: El container tiene que mover la documentacion compilada al host.

WORKDIR /root/LincedIn/LincedIn-TallerII-Server/config/build/bin/

# No es necesario correr el bin del Server ya que es un ciclo infinito que espera interaccion para ser parado.
CMD ["sh", "-c", "/root/LincedIn/LincedIn-TallerII-Server/config/build/bin/RunUnitTests"]
