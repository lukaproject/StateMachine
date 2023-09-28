# 3rd party
add_subdirectory(thirdparty/googletest)
enable_testing()

function(add_test_file TEST_NAME TEST_SRC LINK_LIBS)
  add_executable(${TEST_NAME} ${TEST_SRC})
  target_link_libraries(${TEST_NAME} 
    ${LINK_LIBS}
    GTest::GTest
    GTest::Main
  )
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction(add_test_file)