cmake_minimum_required(VERSION 3.2)
project(VisualStudio2015)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    KentDAW.sln
    KentDAW.vcxproj
    KentDAW.vcxproj.filters
    resources.rc)

add_executable(VisualStudio2015 ${SOURCE_FILES})