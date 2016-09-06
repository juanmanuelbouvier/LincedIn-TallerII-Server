# LincedIn-TallerII-Server ![Build Status](https://travis-ci.org/juanmanuelbouvier/LincedIn-TallerII-Server.svg?branch=master)
Trabajo Práctico de Taller de Programación II 2c-2016 (75.52) | Facultad de Ingeniería - Universidad de Buenos Aires

## Descripción
Server C++ del TP.

### Herramientas
  - CMake
  - Docker
  - Sphinx
  - Doxygen

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
Para ejecutar el proyecto hay que ejecutar el comando `make run`<br />
`El servidor estará escuchando en [localhost:8080](localhost:8080).`<br/>
`El log se guardar en la carpeta logs y también funciona por stdout.`<br/>


#### Sólo Documentación
Para generar documentación del proyecto hay que ejecutar el comando `make doc`<br />
Se genera documentación con dos herramientas distintas: **Sphinx** y **Doxygen**. Se recomienda consultar la documentación de Doxygen pues la de Sphinx podría estar desactualizada al no ser una herramienta de tipo autodoc.<br />
La documentación HTML de Doxygen se encontrará en el archivo _docs/build/doxymentation/html/index.html_<br />
La documentación HTML de Sphinx se encontrará en el archivo _docs/build/sphinx/html/index.html_<br />

#### Limpiar archivos generados por CMake
Para limpiar los archivos generados por CMake hay que ejecutar el comando `make clean`<br />
Este comando remueve los directorios _build_<br />
Borra los archivos generados al compilar y también toda la documentación generada por Sphinx y Doxygen.<br />

### Testing
Para correr los tests unitarios una vez generado el ejecutable del servidor, ejecutar `make test` o ir al directorio `config/build/bin/` y correr `RunUnitTests`.<br />

### Valgrind
Para correr el chequeo de memoria de valgrind, ejecutar el comando `make valgrind` una vez compilado el proyecto y generado el ejecutable correspondiente.<br />

### Docker
Al hacer el `build` del Dockerfile se crea una imagen del entorno con las dependencias instaladas y el proyecto ya compilado. Por ejemplo, utilizar el comando `sudo docker build -t lincedin-appserver .` Es importante que el Dockerfile se encuentre en el directorio raíz del proyecto puesto que los archivos se copian al contenedor de Docker a través del comando `COPY`; es decir, el repositorio no se clona desde el Dockerfile sino que ya debe estar creado previamente.<br />
Al correr la imagen se levanta el servidor dentro del container. Siguiendo con el ejemplo anterior, el comando sería `sudo docker run lincedin-appserver`<br />



