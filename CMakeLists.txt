cmake_minimum_required(VERSION 3.20)
project(P_Center)

set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_CXX_FLAGS}")
include_directories(class)
include_directories(src)
include_directories(test)
include_directories(D:/C++/boost_1_49_0)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(P_Center src/main.cpp class/PCenter.cpp class/PCenter.h class/Set.cpp class/Set.h test/test.cpp test/test.h src/utils.cpp src/utils.h class/Center.cpp class/Center.h class/Element.cpp class/Element.h class/Instance.cpp class/Instance.h class/RandomSet.cpp class/RandomSet.h class/TabuList.cpp class/TabuList.h class/QuickMap.cpp class/QuickMap.h class/Vector.cpp class/Vector.h)
