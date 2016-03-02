cmake_minimum_required(VERSION 3.3)
project(AwesomeOne)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    basiclib.h
    main.cpp)

add_executable(AwesomeOne ${SOURCE_FILES})