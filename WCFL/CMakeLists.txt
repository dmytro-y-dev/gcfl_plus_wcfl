cmake_minimum_required(VERSION 3.1)

project(WCFL)

include_directories(include ../GCFL/include)

FILE(GLOB SOURCE_FILES source/*.cpp)
add_library(WCFL STATIC ${SOURCE_FILES})
target_link_libraries(WCFL GCFL)