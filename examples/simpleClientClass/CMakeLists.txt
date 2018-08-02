cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../CMakeLists.txt)
#add_executable(test test.cpp simpleStreamer.h)
add_executable(test test.cpp)
set_property(TARGET test PROPERTY CXX_STANDARD 11)
set_property(TARGET test PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(test sioclient)
target_link_libraries(test pthread )
message(STATUS ${Boost_INCLUDE_DIRS} )
target_include_directories(test PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/../src"
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR})

