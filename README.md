<base target="_blank">

# Fantasy Clicker
Nueva versión del juego "_Clicker Orcs_", proyecto desarrollado en 2017, desde cero, en **C++ y SFML**, para el final del trayecto "**Programación Avanzada de VJ**" en [Image Campus](https://imagecampus.edu.ar/).

## Devlog
- El juego original (2017) fue programada en **C++ Clásico** -estilo C-. Hacía un uso intensivo de "_raw pointers_", y no incorparaba las nuevas features que el lenguaje fue introduciendo con los distintos estándares desde _C++11_ en adelante. Además, no se manejaban de manera eficiente los assets.

- Hasta el momento se realizaron las siguientes tareas:
  - Port del proyecto, de VS Community 2017 a VS Community 2022.
  - Modificación del formato en general para que la lectura del código se adapte a un estilo más moderno.
  - Refactorización de la API con respecto a la seguridad, pasando de una API "insegura" (uso intensivo de "raw pointers", y gestión manual de la memoria), a una API "segura" con uso de referencias, "const correctness", smart pointers, y RAII.
  - Refactorización del codigo en general, modificando / incorporando nuevas features que proveé el lenguaje desde C++11 en adelante (auto, lambdas, range-based for loops, uniform initializations, reference_wrapper, optional, string_view, constexpr, noexcept, override, =delete, =default, final, move semantics, using, enum class, std::array, std::unordered_map).
  - Implementación de un Asset Manager genérico (gestiona los recursos de sfml que comparten una misma interfaz: sf::Textures, sf::SoundBuffer, sf::Font)
  - Implementación de un gestor único de animaciones.
  - Implementación de un parser de archivos de texto con formato _json_ (utilizando la librería [nlohmann/json](https://github.com/nlohmann/json)), el cúal permite modificar los valores del proyecto sin necesidad de recompilación.
  - Implementación de un componente para gestionar los inputs de teclado. La implementación desacopla la asignación de teclas de las acciones (commands).
 

