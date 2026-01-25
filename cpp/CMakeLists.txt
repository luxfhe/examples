cmake_minimum_required(VERSION 3.20)
project(luxfhe_example CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(luxfhe REQUIRED)

add_executable(fhe_demo main.cpp)
target_link_libraries(fhe_demo luxfhe::luxfhe)
