cmake_minimum_required(VERSION 3.17)
project(cTrace)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(cTrace
        include/Agent.h
        include/Graph.h
        include/json.hpp
        include/Tree.h
        include/Session.h
        src/Agent.cpp
        src/Graph.cpp
        src/main.cpp
        src/Session.cpp
        src/Tree.cpp)