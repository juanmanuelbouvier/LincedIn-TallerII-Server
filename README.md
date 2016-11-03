# LincedIn-TallerII-Server ![Build Status](https://travis-ci.org/juanmanuelbouvier/LincedIn-TallerII-Server.svg?branch=master)
Trabajo Práctico de Taller de Programación II 2c-2016 (75.52) | Facultad de Ingeniería - Universidad de Buenos Aires

## Descripción
Server C++ del TP.

### Herramientas
  - CMake
  - Docker
  - Sphinx
  - Doxygen
  
### Librerias externas
  - [Cesanta/Mongoose](https://github.com/cesanta/mongoose) ![](https://img.shields.io/badge/license-GPL_2-green.svg "License") | [DOC](https://docs.cesanta.com/mongoose/master/#/c-api/http_server.h/mg_serve_http.md/)
  - [Google LevelDB](https://github.com/google/leveldb) | [DOC](https://rawgit.com/google/leveldb/master/doc/index.html)
  - [JSON CPP](https://github.com/open-source-parsers/jsoncpp) | [DOC](http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)

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
Para compilar el proyecto hay que ejecutar el comando `make build`<br />
El ejecutable se creará en el directorio _config/build/bin_<br />

#### Correr
Para ejecutar el proyecto con parametros default hay que ejecutar el comando `make run`<br />
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
		"level": type number			//Sets log level. ERROR(0), WARNING(1), INFO(2), DEBUG(3). Default: 3
		"file": type string			//Set Path to write log. Default: "LincedInAppServer.log"
		"show_in_stdout": type boolean		//If true the logs also be displayed in stdout. Default: true
	},
	"port": type int			//Sets port for incomming connections. Default: 8081
	"shared_server_url": type string	//Url to shared server client. Format "(URL|IP):PORT". Default: "lincedin.herokuapp.com:80"
	"db_folder": type string //Folder designed to store the databases
}

```

#### Sólo Documentación
Para generar documentación del proyecto hay que ejecutar el comando `make doc`<br />
Se genera documentación con dos herramientas distintas: **Sphinx** y **Doxygen**. Se recomienda consultar la documentación de Doxygen pues la de Sphinx podría estar desactualizada al no ser una herramienta de tipo autodoc.<br />
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
Para correr el chequeo de memoria de valgrind, ejecutar el comando `make valgrind` una vez compilado el proyecto y generado el ejecutable correspondiente.<br />

### Docker
Al hacer el `build` del Dockerfile se crea una imagen del entorno con las dependencias instaladas y el proyecto ya compilado. Por ejemplo, utilizar el comando `sudo docker build -t lincedin-appserver .` Es importante que el Dockerfile se encuentre en el directorio raíz del proyecto puesto que los archivos se copian al contenedor de Docker a través del comando `COPY`; es decir, el repositorio no se clona desde el Dockerfile sino que ya debe estar creado previamente.<br />
Al correr la imagen se levanta el servidor dentro del container. Siguiendo con el ejemplo anterior, el comando sería `sudo docker run -p 8080:8080 -t -i lincedin-appserver`<br />
Notar que en el ejemplo anterior se indica explícitamente que el puerto local 8080 está escuchando al puerto 8080 expuesto por el container. Si se desea utilizar otro puerto local debe tenerse en cuenta también que en la app de Android el 8080 está hardcodeado, por lo cual también deberá cambiarse este puerto en el código fuente de la misma.<br />
Por otro lado, los _flags_ `-t` y `-i` permiten correr una terminal interactiva dentro del container.<br />

