cmake_minimum_required(VERSION 3.10)
project(Sleep C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(Sleep
        main.c
        sleep_data.c
        algorithms.c
        ui.c
)