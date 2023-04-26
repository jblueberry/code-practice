add_executable(test_amo test_amo.cpp)
target_link_libraries(test_amo PRIVATE dslabs)
add_executable(test_kv_store test_kv_store.cc)
target_link_libraries(test_kv_store PRIVATE dslabs)

add_executable(gtest_test gtest_test.cc)
target_link_libraries(gtest_test PRIVATE dslabs gtest_main gtest)

add_executable(thread_test thread_test.cc)