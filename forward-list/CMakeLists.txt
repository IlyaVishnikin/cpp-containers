cmake_minimum_required(VERSION 3.2)

project(flist VERSION 1.0.0)

add_executable(flist src/flist.cpp)
add_executable(tests tests/flist_tst.cpp)

target_include_directories(
    flist
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"  
)

target_include_directories(
    tests
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

target_link_libraries(
    tests
    PRIVATE
        gtest gtest_main   
)
