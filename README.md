# LincedIn-TallerII-Server
Trabajo Práctico de Taller de Programación II (75.52) | Facultad de Ingeniería - Universidad de Buenos Aires

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

#### Sólo Documentación
Para generar documentación del proyecto hay que ejecutar el comando `make doc`<br />
Se genera documentación con dos herramientas distintas: **Sphinx** y **Doxygen**. Se recomienda consultar la documentación de Doxygen pues la de Sphinx podría estar desactualizada al no ser una herramienta de tipo autodoc.<br />
La documentación HTML de Doxygen se encontrará en el archivo _docs/build/doxymentation/html/index.html_<br />
La documentación HTML de Sphinx se encontrará en el archivo _docs/build/sphinx/html/index.html_<br />

#### Limpiar archivos generados por CMake
Para limpiar los archivos generados por CMake hay que ejecutar el comando `make clean`<br />
Este comando remueve los directorios _build_<br />
Borra los archivos generados al compilar y también toda la documentación generada por Sphinx y Doxygen.<br />

### Docker
Al hacer el `build` del Dockerfile se crea una imagen del entorno con las dependencias instaladas y el proyecto ya compilado. Por ejemplo, utilizar el comando `sudo docker build -t lincedin-appserver`<br />
Al correr la imagen se levanta el servidor dentro del container. Siguiendo con el ejemplo anterior, el comando sería `sudo docker run lincedin-appserver`<br />



