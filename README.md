# Fantasy Clicker
Nueva versión del juego "_Clicker Orcs_", proyecto desarrollado en 2017, desde cero, en **C++ y SFML**, para el final del trayecto "**Programación Avanzada de VJ**" en [Image Campus](https://external.ink?to=/imagecampus.edu.ar/).

## Devlog
- El juego original (2017) fue programada en **C++ Clásico** -estilo C-. Hacía un uso intensivo de "_raw pointers_", y no incorparaba las nuevas features que el lenguaje fue introduciendo con los distintos estándares desde _C++11_ en adelante.

- En ese sentido, las primeras tareas se orientaron a:
  - Portar el proyecto de VS Community 2017 a VS Community 2022.
  - Modificar el formato para que la lectura de los archivos se adapte a un estilo más moderno.
 
 - Luego, se refactorizó la API en general, pasando de una API "insegura" (uso intensivo de "raw pointers", y gestión manual de la memoria), a una API "segura" con uso de referencias, "const correctness", smart pointers, y RAII.
 
 - A continuación, se refactorizaró el codigo en general, modificando / incorporando las nuevas features que proveé el lenguaje desde C++11 en adelante.
 

