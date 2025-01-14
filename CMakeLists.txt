cmake_minimum_required(VERSION 3.10)
project(cpp_fast)
set (CMAKE_CXX_STANDARD 11)

option (CMAKE_SUPPRESS_REGENERATION "Suppress the cmake macro that causes regeneration of build scripts during build" ON)

SET(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Do not build benchmark tests" FORCE)
SET(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Do not use GTest for benchmark tests" FORCE)
add_subdirectory(benchmark)
include_directories(benchmark/include/benchmark)
include_directories(boost_container)


add_executable(${PROJECT_NAME}
    0_conf.hpp

    algorithm_1.hpp
    algorithm_2.hpp
    algorithm_3.hpp
    algorithm_4.hpp
    algorithm_5.hpp
    algorithm_6.hpp
    algorithm_x.hpp


    container_1.hpp
    container_2.hpp
    container_3.hpp
    container_4.hpp
    container_5.hpp
    container_6.hpp
    container_7.hpp

    mt_1.hpp
    mt_2.hpp
    mt_3.hpp

    util.hpp
    x_start.cpp
    )
target_link_libraries(${PROJECT_NAME} benchmark)
