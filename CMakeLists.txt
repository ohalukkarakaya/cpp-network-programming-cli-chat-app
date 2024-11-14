cmake_minimum_required(VERSION 3.10)
project(cli_chat_app)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/development/global_variables)
include_directories(${CMAKE_SOURCE_DIR}/development/helpers/include)
include_directories(${CMAKE_SOURCE_DIR}/models/include)
include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_SOURCE_DIR}/development/global_variables/*.cpp"
        "${CMAKE_SOURCE_DIR}/development/helpers/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/models/src/*.cpp"
)
add_executable(cli_chat_app ${SRC_FILES} main.cpp)

file(GLOB TEST_FILES
        "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)
add_executable(run_tests ${TEST_FILES} ${SRC_FILES}) # main.cpp HARİÇ!

target_link_libraries(run_tests gtest gtest_main pthread)

enable_testing()
add_test(NAME RunAllTests COMMAND run_tests)
