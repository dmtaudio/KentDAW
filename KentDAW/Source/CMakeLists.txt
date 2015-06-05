cmake_minimum_required(VERSION 3.2)
project(Source)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    AudioEngine/ArrangeAudioRegions.cpp
    AudioEngine/ArrangeAudioRegions.h
    AudioEngine/AudioEngine.cpp
    AudioEngine/AudioEngine.h
    BinaryData.cpp
    BinaryData.h
    Main.cpp
    MainComponent.cpp
    MainComponent.h
    Transport.cpp
    Transport.h)

add_executable(Source ${SOURCE_FILES})