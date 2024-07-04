cmake_minimum_required(VERSION 3.13)

project(redis-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
)


set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(main ${SOURCE_FILES} src/main.cpp
        src/Server.cpp
        include/Server.h
        include/Protocol.h
        include/Command.h
        include/Error.h
        include/Utils.h
        include/stringzilla/experimental.h
        include/stringzilla/stringzilla.h
        include/stringzilla/stringzilla.hpp
)

target_link_libraries(main PRIVATE Threads::Threads)