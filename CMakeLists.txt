cmake_minimum_required(VERSION 2.8.0)
project(esper)

include_directories(include)

file(GLOB SOURCES "include/**/*.h")
file(GLOB SOURCES "include/**/*.cpp")

add_library(esper SHARED ${SOURCES})

install(TARGETS esper DESTINATION ./lib)