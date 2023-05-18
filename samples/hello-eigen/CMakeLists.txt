cmake_minimum_required(VERSION 3.21)
project(hello-eigen)

#find eigen
# include(cmake/find_eigen3.cmake)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
message(STATUS "EIGEN3_VERSION: ${EIGEN3_VERSION_STRING}")

#notice the "recycling" of CMAKE_C_FLAGS
#this is necessary to pick up android flags
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic" )

# add_library(hello-eigen SHARED hello-eigen.cpp)
#target_link_libraries(hello-eigen)
add_executable(hello_eigen hello_eigen.cpp)

add_executable(isometry3d isometry3d.cpp)
