cmake_minimum_required(VERSION 3.20)
project(P_Center)

set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_CXX_FLAGS}")

include_directories(class)
include_directories(src)
include_directories(test)
set(CMAKE_CXX_STANDARD 17)

add_executable(P_Center src/main.cpp class/PCenter.cpp class/PCenter.h class/Set.cpp class/Set.h test/test.cpp test/test.h src/utils.cpp src/utils.h class/Center.cpp class/Center.h class/Element.cpp class/Element.h class/Instance.cpp class/Instance.h)
