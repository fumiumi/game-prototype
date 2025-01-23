cmake_minimum_required(VERSION 3.15)
project(game-prototype)

# C++バージョン設定（必要に応じて変更）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build typeが指定されていない場合はDebugにしておく（任意）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# --- Find or Add external libraries ---
# 1) GLAD (ソースをプロジェクト内に取り込んでいる場合)
# add_subdirectory(external/glad)

# 2) GLFW (パッケージマネージャでインストール or find_package)
find_package(glfw3 REQUIRED) 
# Windowsの場合: vcpkgインストール後、 cmake実行時に -DCMAKE_TOOLCHAIN_FILE=[vcpkg path]/scripts/buildsystems/vcpkg.cmake など
# macOSの場合: brew install glfw && find_package(glfw3 REQUIRED)

# OpenGLはOSにより別の指定が必要
if (APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
    set(OPENGL_LIBS ${OpenGL_LIBRARY})
elseif (UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    set(OPENGL_LIBS OpenGL::GL)
endif()

# ソースファイルの指定
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# 実行ファイルの生成
add_executable(game-prototype ${SRC_FILES})

# Gladを使用している場合はリンクする
# target_link_libraries(game-prototype PRIVATE glad)

# GLFWをリンク
target_link_libraries(game-prototype PRIVATE glfw)

# OpenGLをリンク
target_link_libraries(game-prototype PRIVATE ${OPENGL_LIBS})

# 例: 
add_library(glad STATIC src/glad/glad.c)
target_include_directories(glad PUBLIC src/glad)

# --- GTestを使ったテストビルドの設定 ---
enable_testing()

# GTestのソースをサブディレクトリで使う場合
# add_subdirectory(external/googletest)
# include_directories(external/googletest/googletest/include)
# include_directories(external/googletest/googlemock/include)

file(GLOB TEST_FILES
    "${PROJECT_SOURCE_DIR}/tests/*.cpp"
)

# add_executable(game-prototypeTests ${TEST_FILES})

# Windows/macOS共通でGTestライブラリをリンクする
# - find_packageの場合
# find_package(GTest REQUIRED)
# target_link_libraries(game-prototypeTests PRIVATE GTest::gtest GTest::gtest_main)

# - subdirectoryの場合
# target_link_libraries(game-prototypeTests PRIVATE gtest gtest_main)

target_link_libraries(game-prototypeTests PRIVATE ${OPENGL_LIBS} glfw)
# テストでもOpenGLやGLFWに依存するパーツがあるなら同様にリンク

# テスト実行のターゲット
add_test(NAME game-prototypeTests COMMAND game-prototypeTests)
