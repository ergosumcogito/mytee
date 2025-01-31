cmake_minimum_required(VERSION 3.30)
project(mytee C)

set(CMAKE_C_STANDARD 17)


# Add custom target to use the Makefile
add_custom_target(
        make_all
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Add custom target for clean (optional)
add_custom_target(
        make_clean
        COMMAND make clean
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c")

add_executable(YourExecutable ${SOURCES})
