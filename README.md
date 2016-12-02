# LincedIn-TallerII-Server ![Build Status](https://travis-ci.org/juanmanuelbouvier/LincedIn-TallerII-Server.svg?branch=master)
Trabajo Práctico de Taller de Programación II 2c-2016 (75.52) | Facultad de Ingeniería - Universidad de Buenos Aires

## Descripción
Server C++ del TP.

### Herramientas
  - CMake 
  - Docker
  - Sphinx
  - Doxygen
  - LCov (gCov)
  - ElasticSearch (via Docker)
  
### Librerias externas
  - [Cesanta/Mongoose](https://github.com/cesanta/mongoose) ![](https://img.shields.io/badge/license-GPL_2-green.svg "License") | [DOC](https://docs.cesanta.com/mongoose/master/#/c-api/http_server.h/mg_serve_http.md/)
  - [Google LevelDB](https://github.com/google/leveldb) | [DOC](https://rawgit.com/google/leveldb/master/doc/index.html)
  - [JSON CPP](https://github.com/open-source-parsers/jsoncpp) | [DOC](http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)
  - [JWT](https://github.com/benmcollins/libjwt)

### Integrantes:
  - Octavio Iogha
  - Etchanchú Facundo
  - Bouvier Juan Manuel
  - Bert Tomás

## Instrucciones

### CMake
El comando `make` compila el proyecto y además genera automáticamente documentación del proyecto.<br />
Todos los archivos generados por CMake (temporales o no) se guardan en directorios _build_ dentro de cada directorio particular donde se ejecuten instrucciones CMake.<br />

#### Sólo Compilación
Se recomienda instalar las siguientes aplicaciones para compilar el proyect:
`sudo apt-get install g++ make cmake valgrind doxygen graphviz python3-setuptools pkg-config libsnappy-dev libleveldb-dev lcov libjansson-dev openssl libssl-dev`
Para compilar el proyecto hay que ejecutar el comando `make build`<br />
El ejecutable se creará en el directorio _config/build/bin_<br />

#### Correr
Para ejecutar el proyecto con parametros default hay que ejecutar el comando `make run`<br />
Ademas, se debe correr el container de elasticsearch para poder realizar busquedas (el server puede funcionar normalmente sin este feature). Para correr el container se debe hacer `sudo docker run -p 9200:9200 elasticsearch`. Si el container lanza error al intentar levantarse se debe correr el comando `sudo sysctl -w vm.max_map_count=262144` sobre el host.
El servidor estará escuchando en: [localhost:8081](http://localhost:8081).<br/>
`El log se guardar en la carpeta logs y también funciona por stdout.`<br/><br/>

Para ver ayuda y versión `./config/build/bin/LincedInAppServer -h`<br/>
Parametros:<br/>
`$./LincedInAppServer -s [SETTINGS FILE] `<br/>
- **SETTINGS:** Path to setting file (json)	Default: "settings/setting.json"<br/>

##### Setting JSON structure
```javascript
{
	"logger": {
		//Sets log level. ERROR(0), WARNING(1), INFO(2), DEBUG(3). Default: 3
		"level": type number
		
		//Set Path to write log. Default: "LincedInAppServer.log"
		"file": type string			
		
		//If true the logs also be displayed in stdout. Default: true
		"show_in_stdout": type boolean		
	},
	
	//Sets port for incomming connections. Default: 8081
	"port": type int			
	
	//Url to shared server client. Format "(URL|IP):PORT". Default: "lincedin.herokuapp.com:80"
	"shared_server_url": type string	
	
	//Folder designed to store the databases
	"db_folder": type string 
	
	//Firebase parameters. 
	//	Default url: "fcm.googleapis.com"
	//	Default key: "AIzaSyBE9xn7X8eo86rxJ_ggiQt6IPx-Oxsb1Kg" 
	"firebase_url": type string,
	"firebase_api_key": type string,
	
	//Elastic search host. Default "localhost:9200"
	"elastic_host": type string
}

```

#### Sólo Documentación
Para generar documentación del proyecto hay que ejecutar el comando `make doc`<br />
Se genera documentación con dos herramientas distintas: **Sphinx** y **Doxygen**. 
_Nota: Se recomienda consultar la documentación de Doxygen pues la de Sphinx podría estar desactualizada al no ser una herramienta de tipo autodoc._<br />
La documentación HTML de Doxygen se encontrará en el archivo _docs/build/doxymentation/html/index.html_<br />
La documentación HTML de Sphinx se encontrará en el archivo _docs/build/sphinx/html/index.html_<br />

#### Estructura de Base de datos.
Ver estructura de la base de datos [aquí](docs/database/README.md)

#### Limpiar archivos generados por CMake
Para limpiar los archivos generados por CMake hay que ejecutar el comando `make clean`<br />
Este comando remueve los directorios _build_<br />
Borra los archivos generados al compilar y también toda la documentación generada por Sphinx y Doxygen.<br />

### Testing
Para correr los tests unitarios una vez generado el ejecutable del servidor, ejecutar `make test` o ir al directorio `config/build/bin/` y correr `RunUnitTests`.<br />

### Coverage
El coverage de los test se genera con el comando `make coverage-test`. Para visualizar los resultados abrir con el navegador el archivo `/config/build/coverage/index.html`.

### Valgrind
Para correr el chequeo de memoria de valgrind, ejecutar el comando `make valgrind` o `make valgrind-test` una vez compilado el proyecto y generado el ejecutable correspondiente.<br />

### Documentacion de la RESTful API
Para ver de una forma mas amigable la documentacion de la rest api ingresar [aqui](wiki/RESTful-API)

### Docker
Alternativamente, para no instalar todas las dependencias en el host, se creo un compose de docker en la cual se "virtualiza" ubuntu y se puede levantar el server y escuchar en el puerto indicado.<br/>
**IMPORTANTE**: 
	- En el setting.json se debe tener "elastic:9200" en el member "elastic_host". 
	- El puerto en este archivo debe ser 8081. Si se desea cambiar el puerto, hay que modificar el Dockerfile y crear la imagen nuevamente.
	- Si hay problemas con el container de elastic search (_"bootstrap error"_) debe correrse el siguiente comando sobre el host: `sudo sysctl -w vm.max_map_count=262144`

Para correr docker hacer:
`sudo docker-compose build`
`sudo docker-compose up`

Notas:
	- El log de la ejecucion se guarda en la carpeta logs del host.
	- El setting es leido desde el host (puede modificarse y no es necesario rehacer el build)
	- La carpeta db es compartida entre host-container. Esto permite que los datos no dependan de Docker y haya persistencia. Es decir, podes levantar el server via Docker, trabajar y luego podes eliminar los containers e imagenes que las bases de datos no se van a perder.


