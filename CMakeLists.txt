cmake_minimum_required(VERSION 3.10)

project(StateMachine)

option(LUKA_STATEMACHINE_TEST "enable test cases" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glog.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gtest.cmake)

# library
set(LUKAPROJECT_STATEMACHINE_LIB StateMachine)
file(GLOB SRCS src/*.cc)
message("SOURCES:  ${SRCS}")
add_library(${LUKAPROJECT_STATEMACHINE_LIB} 
  ${SRCS}
)
target_link_libraries(${LUKAPROJECT_STATEMACHINE_LIB} glog::glog)
target_include_directories(${LUKAPROJECT_STATEMACHINE_LIB} PUBLIC ${PROJECT_SOURCE_DIR}/include)


if (LUKA_STATEMACHINE_TEST)
  message("enable statemachine test cases")
  add_test_file(general_tests tests/general_tests.cc ${LUKAPROJECT_STATEMACHINE_LIB})
  add_test_file(event_tests tests/event_tests.cc ${LUKAPROJECT_STATEMACHINE_LIB})
else()
  message("disable statemachine test cases")
endif(LUKA_STATEMACHINE_TEST)
