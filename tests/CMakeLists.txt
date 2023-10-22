cmake_minimum_required(VERSION 3.11)

project(
  StateMachine_Test
  LANGUAGES CXX
)

add_test_file(general_tests general_tests.cc LukaProject::StateMachine)
add_test_file(event_tests event_tests.cc LukaProject::StateMachine)
add_test_file(fa_tests fa_tests.cc LukaProject::StateMachine)