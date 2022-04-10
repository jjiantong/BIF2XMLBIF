cmake_minimum_required(VERSION 3.16)
project(BIF2XMLBIF)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SRC *.cpp)
file(GLOB HEAD *.h)

add_executable(BIF2XMLBIF ${SRC} ${HEAD})