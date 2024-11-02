cmake_minimum_required(VERSION 3.10)
project(MyChatApp)

# C++ standardını ayarla
set(CMAKE_CXX_STANDARD 17)

# Google Test'i FetchContent ile indir
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

# Proje başlık dosyalarını ekleyin
include_directories(${CMAKE_SOURCE_DIR}/development/global_variables)
include_directories(${CMAKE_SOURCE_DIR}/development/helpers/include)
include_directories(${CMAKE_SOURCE_DIR}/models/include)
include_directories(${gtest_SOURCE_DIR}/include) # Google Test başlık dosyaları

# Ana uygulama hedefini oluştur
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_SOURCE_DIR}/development/global_variables/*.cpp"
        "${CMAKE_SOURCE_DIR}/development/helpers/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/models/src/*.cpp"
)
add_executable(MyChatApp ${SRC_FILES} main.cpp) # Ana programın main.cpp'si burada

# Test hedefini oluştur (main.cpp'yi dahil etmeyin!)
file(GLOB TEST_FILES
        "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)
add_executable(run_tests ${TEST_FILES} ${SRC_FILES}) # main.cpp HARİÇ!

# Google Test'i ve testler için kütüphaneleri bağla
target_link_libraries(run_tests gtest gtest_main pthread)

# Testleri tanımla
enable_testing()
add_test(NAME RunAllTests COMMAND run_tests)
