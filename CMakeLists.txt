cmake_minimum_required(VERSION 3.13)

project(redis-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(main ${SOURCE_FILES} src/main.cpp
        src/Server.cpp
        src/Server.h
        src/Protocol.h
        src/Command.h
        src/Error.h
        src/Utils.h
        src/Reply.h
        src/Reply.h
        src/BulkStringReply.cpp
        src/BulkStringReply.h
        src/SimpleStringReply.cpp
        src/SimpleStringReply.h
        src/RedisDB.cpp
        src/RedisDB.h
)

target_link_libraries(main PRIVATE Threads::Threads)