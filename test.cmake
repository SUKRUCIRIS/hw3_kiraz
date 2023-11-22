
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

#
# test
#

add_executable(test_hw1 kiraz/test/test_hw1.cc ${FLEX_HW1_LEXER_OUTPUTS})
target_link_libraries(test_hw1 kiraz GTest::gtest_main ${FLEX_LIBRARIES})
gtest_discover_tests(test_hw1)

add_executable(test_hw2 kiraz/test/test_hw2.cc ${FLEX_HW2_LEXER_OUTPUTS} ${BISON_HW2_PARSER_OUTPUTS})
target_link_libraries(test_hw2 kiraz GTest::gtest_main ${FLEX_LIBRARIES})
gtest_discover_tests(test_hw2)

add_executable(test_hw3 kiraz/test/test_hw3.cc ${FLEX_HW3_LEXER_OUTPUTS} ${BISON_HW3_PARSER_OUTPUTS})
target_link_libraries(test_hw3 kiraz GTest::gtest_main ${FLEX_LIBRARIES})
gtest_discover_tests(test_hw3)
