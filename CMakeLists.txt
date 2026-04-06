cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
project(VaultSecretsMod VERSION 1.0.0)

add_library(VaultSecretsMod SHARED src/main.cpp)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK no está definido")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
target_link_libraries(VaultSecretsMod geode-sdk)
setup_geode_mod(VaultSecretsMod)
