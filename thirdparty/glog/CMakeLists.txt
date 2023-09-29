configure_file(CMakeLists.txt.in glog/CMakeLists.txt)

set(WITH_UNWIND OFF)
set(WITH_GFLAGS OFF)
set(WITH_GTEST  OFF)

include(CTest)

set(BUILD_TESTING OFF)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glog )
if(result)
  message(FATAL_ERROR "CMake step for glog failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glog )
if(result)
  message(FATAL_ERROR "Build step for glog failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/glog-src
                 ${CMAKE_CURRENT_BINARY_DIR}/glog-build)


if(NOT TARGET glog::glog)
  add_library(glog::glog ALIAS glog)
endif()
