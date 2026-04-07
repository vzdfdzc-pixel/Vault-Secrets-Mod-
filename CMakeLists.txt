cmake_minimum_required(VERSION 3.20.0)

project(mod_67mode CXX)

set(GEODE_SDK $ENV{GEODE_SDK})
add_subdirectory(${GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode-sdk)

add_library(${PROJECT_NAME} SHARED src/main.cpp)
setup_geode_mod(${PROJECT_NAME})
