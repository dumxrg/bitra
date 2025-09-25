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

# Crea el ejecutable
add_executable(bitra ${SOURCES})

# Librerías necesarias
# Si usas raylib instalada en el sistema
find_package(raylib REQUIRED)

# Enlaza raylib y otras dependencias de sistema
target_link_libraries(bitra PRIVATE raylib m pthread dl rt X11)

# Instala los assets en el mismo directorio del binario
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
