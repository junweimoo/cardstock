cmake_minimum_required(VERSION 3.26)
project(imgengine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# --- Python + nanobind -----------------------------------------------------
find_package(Python 3.9 REQUIRED COMPONENTS Interpreter Development.Module)

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

# --- Native dependencies ---------------------------------------------------
find_package(PNG REQUIRED)          # libpng for M0 PNG output

# --- Core static library ---------------------------------------------------
add_library(imgengine_core STATIC
  src/core/image_buffer.cpp)
target_include_directories(imgengine_core PUBLIC src)
target_link_libraries(imgengine_core PUBLIC PNG::PNG)

# Static lib is linked into the _imgengine shared module, so its objects
# must be position-independent (PIC).
set_target_properties(imgengine_core PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(imgengine_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- Python extension module ----------------------------------------------
nanobind_add_module(_imgengine src/bindings/module.cpp)
target_link_libraries(_imgengine PRIVATE imgengine_core)

install(TARGETS _imgengine LIBRARY DESTINATION imgengine)
