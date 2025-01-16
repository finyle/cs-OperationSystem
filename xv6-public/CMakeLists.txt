CMAKE_MINIMUM_REQUIRED(3.22)
project(xv6)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_SOURCE_DIR}/)

add_executable(main z_exp/z_leet.c)