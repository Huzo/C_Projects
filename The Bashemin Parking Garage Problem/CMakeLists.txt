cmake_minimum_required(VERSION 3.9)
project(Q3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Q3 main.c car.c stackar.c)
link_libraries(car.h stackar.c fatal.h)
