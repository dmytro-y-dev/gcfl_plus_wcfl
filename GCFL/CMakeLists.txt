cmake_minimum_required(VERSION 3.1)

project(GCFL)

include_directories(include)

FILE(GLOB SOURCE_FILES source/*.cpp)
add_library(GCFL STATIC ${SOURCE_FILES})