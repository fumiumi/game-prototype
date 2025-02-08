# テスト用の構成ファイル

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG release-1.15.0 # v1.15.0
# )
# FetchContent_MakeAvailable(googletest)

# ローカルのgoogletestを使う
if(WIN32)
elseif(APPLE)
  find_package(GTest REQUIRED)
endif()

# テストテスト
set(SANDBOX_FILE_DIR ${PROJECT_SOURCE_DIR}/src/sandbox)
# サンプルテストプロジェクト1
set(TEST_PROJECT_NAME1 ${PROJECT_NAME}_tests1)
add_executable(${TEST_PROJECT_NAME1}
  sandbox/Test_hoge.cpp
)
target_link_libraries(${TEST_PROJECT_NAME1} PRIVATE
GTest::gtest
GTest::gtest_main
GTest::gmock
GTest::gmock_main
)
add_test(NAME ${TEST_PROJECT_NAME1} COMMAND ${TEST_PROJECT_NAME1})
message(STATUS "Sample test1 has successfully added.")

# サンプルテストプロジェクト2
# set(TEST_PROJECT_NAME2 ${PROJECT_NAME}_tests2)
# add_executable(${TEST_PROJECT_NAME2}
#   sandbox/Test_Math.cpp
# )
# target_link_libraries(${TEST_PROJECT_NAME2} PRIVATE
# GTest::gtest
# GTest::gtest_main
# GTest::gmock
# GTest::gmock_main
# )
# add_test(NAME ${TEST_PROJECT_NAME2} COMMAND ${TEST_PROJECT_NAME2})
# message(STATUS "Sample test2 has successfully added.")
