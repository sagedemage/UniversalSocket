cmake_minimum_required(VERSION 3.22 VERSION 0.1.0)

project(cli_app)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(STANDARD_CXX_VERSION_FLAG "-std=c23")
set(OPTIMIZE_FLAG "-O3")
set(WARNING_FLAGS "-Werror -Wpedantic -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STANDARD_CXX_VERSION_FLAG} ${OPTIMIZE_FLAG} ${WARNING_FLAGS}")

add_executable(server 
    server.c
)