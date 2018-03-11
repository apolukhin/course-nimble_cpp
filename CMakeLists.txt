cmake_minimum_required(VERSION 2.8)

if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()


SET(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Do not build benchmark tests" FORCE)
SET(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Do not use GTest for benchmark tests" FORCE)
add_subdirectory(benchmark)
include_directories(benchmark/include/benchmark)
include_directories(boost_container)

project(cpp_fast)
add_executable(${PROJECT_NAME}
    algorithm_common.hpp
    algorithm_1.hpp
    algorithm_2.hpp
    algorithm_3.hpp
    algorithm_4.hpp
    algorithm_5.hpp
    algorithm_6.hpp
    algorithm_x.hpp


    container_common.hpp
    container_1.hpp
    container_2.hpp
    container_3.hpp
    container_4.hpp
    container_5.hpp
    container_6.hpp
    container_7.hpp

    mt_common.hpp
    mt_1.hpp
    mt_2.hpp

    main.cpp
    )
target_link_libraries(${PROJECT_NAME} benchmark)