cmake_minimum_required(VERSION 2.8.7)

find_package( Boost REQUIRED )
if (Boost_FOUND)
    include_directories(BEFORE ${Boost_INCLUDE_DIR})
endif()

SET(CMAKE_CXX_FLAGS                "-Wall -pedantic -std=c++11")

add_executable(tests tests.cpp impl.cpp)