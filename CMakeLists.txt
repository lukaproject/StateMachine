cmake_minimum_required(VERSION 3.11)

project(
  StateMachine
  VERSION 0.0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glog.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gtest.cmake)

# library
set(LUKAPROJECT_STATEMACHINE_LIB StateMachine)
file(GLOB SRCS src/*.cc)
message("SOURCES: ${SRCS}")
add_library(
  ${LUKAPROJECT_STATEMACHINE_LIB}
  STATIC
  ${SRCS}
)
target_link_libraries(${LUKAPROJECT_STATEMACHINE_LIB})
target_include_directories(${LUKAPROJECT_STATEMACHINE_LIB} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(LukaProject::StateMachine ALIAS ${LUKAPROJECT_STATEMACHINE_LIB})

include(CTest)

if (BUILD_TESTING)
  message("enable statemachine test cases")
  add_subdirectory(tests)
else()
  message("disable statemachine test cases")
endif()
