# --- お作法 ---
cmake_minimum_required(VERSION 3.15)

# プロジェクト名
# ${PROJECT_NAME}でプロジェクト名を参照できる
project(game-prototype)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ソースファイルの指定
# HACK: 公式ドキュメントでは明示的なファイル指定を推奨しています。
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(game-prototype ${SRC_FILES})

# --- プロジェクトの設定 ---
# 設定用のヘッダファイルをコピー
configure_file(GamePrototypeConfig.h.in GamePrototypeConfig.h)

# Build typeが指定されていない場合はDebugにしておく（任意）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# --- ライブラリの検索とリンク ---

# 1. Vulkan
if(WIN32)
    # WIN32は、CMakeでWindows全般（32ビットおよび64ビット）を示すリテラル
    find_package(Vulkan REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
    message(STATUS "Vulkan found on Windows: ${Vulkan_LIBRARIES}")
elseif(APPLE)
    # macOSの場合 (MoltenVKを使用)
    set(VULKAN_SDK "/path/to/vulkan-sdk-macos") # まずmacos用のVulkan SDKのパスを変数化
    set(Vulkan_INCLUDE_DIRS "${VULKAN_SDK}/include") # インクルードファイルのパス
    set(Vulkan_LIBRARIES "${VULKAN_SDK}/lib/libMoltenVK.dylib") # MoltenVKのライブラリパス
    target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
    message(STATUS "Vulkan configured for macOS using MoltenVK")
else()
    # APIの取得に失敗したらエラー
    message(FATAL_ERROR "Unsupported operating system")
endif()

# 2. GLFW, GLM
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE glfw) # glmはヘッダオンリーライブラリなので不要
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm::glm)

# --- GTestを使ったテストビルドの設定 ---

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT TAG b514bdc898e2951020cbdca1304b75f5950d1f59 # v1.15.2
)
FetchContent_MakeAvailable(googletest)

# テスト用ターゲットの設定
# CMake only generates tests if the enable_testing() command has been invoked
enable_testing()
# TestMain.cppでRUN_ALL_TESTSしているので、TestMain.cppだけを指定すればよい
add_executable(${PROJECT_NAME}_tests tests/TestMain.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest gtest_main ${PROJECT_NAME})
# COMMAND: Specify the test command-line to run
add_test(
    NAME ${PROJECT_NAME}_tests
    COMMAND ${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests # しばしば${CMAKE_CURRENT_BINARY_DIR}を使うこともあります。
)

# --- ビルド設定 ---
# add the binary tree to the search path for include files
# so that we will find GamePrototypeConfig.h
target_include_directories(game-prototype PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
)

# Windowsの場合: vcpkgインストール後、 cmake実行時に -DCMAKE_TOOLCHAIN_FILE=[vcpkg path]/scripts/buildsystems/vcpkg.cmake など
# macOSの場合: brew install glfw && find_package(glfw3 REQUIRED)