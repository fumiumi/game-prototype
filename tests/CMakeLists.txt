# テスト用の構成ファイル

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)


# ----------------------------------------

# サンプルテストプロジェクト1
set(TEST_PROJECT_NAME1 ${PROJECT_NAME}_tests1)
add_executable(${TEST_PROJECT_NAME1} 
  Test_hoge.cpp
)
target_link_libraries(${TEST_PROJECT_NAME1} PRIVATE 
  gtest 
  gtest_main 
  test-target
)
add_test(NAME ${TEST_PROJECT_NAME1} COMMAND ${TEST_PROJECT_NAME1})

# サンプルテストプロジェクト2
set(TEST_PROJECT_NAME2 ${PROJECT_NAME}_tests2)
add_executable(${TEST_PROJECT_NAME2} 
  Test_Math.cpp
)
target_link_libraries(${TEST_PROJECT_NAME2} PRIVATE 
  gtest 
  gtest_main 
  test-target
)
add_test(NAME ${TEST_PROJECT_NAME2} COMMAND ${TEST_PROJECT_NAME2})