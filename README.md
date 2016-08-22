# LincedIn-TallerII-Server
Trabajo Práctico de Taller de Programación II (75.52) | Facultad de Ingeniería - Universidad de Buenos Aires

## Descripción
Server C++ del TP.

### Herramientas
  - CMake
  - Sphinx

### Integrantes:
  - Octavio Iogha
  - Etchanchú Facundo
  - Bouvier Juan Manuel
  - Bert Tomás

## Instrucciones CMake

El comando `make` compila el proyecto, genera un ejecutable y además genera automáticamente documentación HTML del proyecto.<br />
Todos los archivos generados por CMake (temporales o no) se guardan en directorios _build_ dentro de cada directorio particular donde se ejecuten instrucciones CMake.<br />

### Sólo Compilación
Para compilar el proyecto hay que ejecutar el comando `make build`<br />
El ejecutable se creará en el directorio _config/build/bin_<br />

### Sólo Documentación
Para generar documentación HTML del proyecto hay que ejecutar el comando `make doc`<br />
La documentación se encontrará en el archivo _docs/build/html/index.html_<br />

### Limpiar archivos generados por CMake
Para limpiar los archivos generados por CMake hay que ejecutar el comando `make clean`<br />
Este comando remueve los directorios _build_<br />


