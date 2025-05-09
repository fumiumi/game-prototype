cmake_minimum_required(VERSION 3.23)

# プロジェクト名
# ${PROJECT_NAME}でプロジェクト名を参照できる
project(game_prototype)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# config
# ゲームのバージョンを指定
set(game_prototype_VERSION_MAJOR 0)
set(game_prototype_VERSION_MINOR 1)

# 一旦テスト無効化
# enable_testing()

# openGLのバージョンを指定
# macosではOpenGL4.1まででサポートを辞めた
set(OpenGL_VERSION_MAJOR 4)
set(OpenGL_VERSION_MINOR 1)

configure_file(config.h.in config.h)

# --- ソースファイルの追加 ---
# 各サブシステムディレクトリを変数に格納
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# エンジン部分のサブモジュール
add_subdirectory(${SOURCE_DIR})
# gteatsのサブモジュール
# add_subdirectory(tests)

add_executable(${PROJECT_NAME}
  ${SOURCE_DIR}/Main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE engine_renderer_shader)

# Build typeが指定されていない場合はDebugにしておく（任意）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# --- ライブラリの検索とリンク ---

# --- 外部ライブラリの検索パスを追加 ---
# OpenGL
find_package(OpenGL REQUIRED)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
endif()
message(STATUS "OpenGL found: ${OPENGL_gl_LIBRARY}")

# GLFW
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
message(STATUS "GLFW found: ${GLFW_LIBRARY}")

# OpenAL-Soft
if(WIN32)
  find_package(OpenAL CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL)
  message(STATUS "OpenAL found: ${OPENAL_LIBRARY}")
elseif(APPLE)
  find_package(OpenAL REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL)
  message(STATUS "OpenAL found: ${OPENAL_LIBRARY}")
endif()

# glm
if(WIN32)
  find_package(glm CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
  message(STATUS "GLM found: ${GLM_LIBRARY}")
elseif(APPLE)
  find_package(glm REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
  message(STATUS "GLM found: ${GLM_LIBRARY}")
endif()

# --- externディレクトリのライブラリをリンク ---
# externディレクトリを変数に格納
set(EXTERN_DIR ${PROJECT_SOURCE_DIR}/extern)

# GLAD
if(APPLE)
  set(GLAD_LIBRARY ${EXTERN_DIR}/glad)
  target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_LIBRARY}/include)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${GLAD_LIBRARY}/library/libglad.a)
  message(STATUS "GLAD found: ${GLAD_LIBRARY}")
elseif(WIN32)
  find_package(glad CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
  message(STATUS "GLAD found: ${GLAD_LIBRARY}")
endif()

# Lua
if(APPLE)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(LUA REQUIRED lua) # brew の lua.pc を参照

  target_include_directories(${PROJECT_NAME} PRIVATE
    ${LUA_INCLUDE_DIRS}
  )
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LUA_LIBRARIES}
  )
  message(STATUS "Lua found: ${LUA_LIBRARY}")
elseif(WIN32)
  find_package(Lua CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE lua::lua)
  message(STATUS "Lua found: ${LUA_LIBRARY}")
endif()

# json
target_include_directories(${PROJECT_NAME} PRIVATE
  ${EXTERN_DIR}/json
)
message(STATUS "json.hpp found")

# stb_image
target_include_directories(${PROJECT_NAME} PRIVATE
  ${EXTERN_DIR}/stb
)
message(STATUS "stb found")

# --- ローカル環境のライブラリをリンク ---
# Box2D
if(APPLE)
  set(BOX2D_DIR /opt/homebrew/opt/box2d)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${BOX2D_DIR}/lib/libbox2d.dylib
    ${BOX2D_DIR}/lib/libbox2d.3.dylib
    ${BOX2D_DIR}/lib/libbox2d.3.0.0.dylib
  )
  target_include_directories(${PROJECT_NAME} PRIVATE ${BOX2D_DIR}/include/box2d)
  message(STATUS "Box2D found: ${BOX2D_LIBRARY}")
elseif(WIN32)
  find_package(box2d CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE box2d::box2d)
  message(STATUS "Box2D found: ${BOX2D_LIBRARY}")
endif()

# freetype
if(WIN32)
  find_package(freetype-gl CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE freetype-gl)
  message(STATUS "freetype found")
elseif(APPLE)
  set(FREETYPE_DIR /opt/homebrew)
  target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_DIR}/include/freetype-gl)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${FREETYPE_DIR}/lib64/libfreetype-gl.a
  )
  message(STATUS "freetype found: ${FREETYPE_LIBRARY}")
endif()

message(STATUS "Configured main project: ${PROJECT_NAME}")

# --- ビルド設定 ---
# add the binary tree to the search path for include files
# so that we will find GamePrototypeConfig.h
target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}"
)
