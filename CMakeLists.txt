cmake_minimum_required(VERSION 3.16)
project(bitra)

# C++ estándar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opciones de compilación optimizadas
add_compile_options(
    -O3
    -march=native
    -flto
    -fno-exceptions
    -fno-rtti
    -Wall
    -Wextra
)

# Incluye los headers
include_directories(include)

# Busca todos los archivos fuente en src/
file(GLOB SOURCES "src/*.cpp")

# --- CONFIGURACIÓN DE RAYLIB LOCAL ---
# Desactiva instalación global y ejemplos
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Añade raylib como subdirectorio (clonada en ./external/raylib o similar)
add_subdirectory(external/raylib)

# Añade el ejecutable
add_executable(bitra ${SOURCES})

# Enlaza con raylib (compilada localmente)
target_link_libraries(bitra PRIVATE raylib)

# Enlaza con librerías del sistema necesarias en Linux
if(UNIX)
    target_link_libraries(bitra PRIVATE m pthread dl rt X11 GL)
endif()

# Instala los assets en el mismo directorio del binario
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
