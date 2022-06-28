cmake_minimum_required(VERSION 3.10)
project(typetrainer VERSION 1.2.0 LANGUAGES CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(tt tt.cpp player.cpp cli.cpp engine.cpp database.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
target_compile_features(tt PUBLIC cxx_std_17)
target_link_libraries(tt ${CURSES_LIBRARIES})

add_executable(spl ../tools/text_splitter.cpp)
target_compile_features(spl PUBLIC cxx_std_17)

add_executable(gen ../tools/text_generator.cpp)
target_compile_features(gen PUBLIC cxx_std_17)
