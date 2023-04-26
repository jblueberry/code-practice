add_test([=[HelloTest.BasicAssertions]=]  /home/junhui/code-practice/dslabs-cpp/build/test/gtest_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/junhui/code-practice/dslabs-cpp/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  gtest_test_TESTS HelloTest.BasicAssertions)
