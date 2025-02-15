cmake_minimum_required(VERSION 3.30)
project(mytee C)

set(CMAKE_C_STANDARD 17)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "src/*.c")
add_executable(YourExecutable ${SOURCES})

# Add test sources
file(GLOB TEST_SOURCES "tests/*.c")
if(TEST_SOURCES)
    add_executable(TestExecutable ${TEST_SOURCES})
    target_include_directories(TestExecutable PRIVATE ${CMAKE_SOURCE_DIR}/include)
endif()

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
