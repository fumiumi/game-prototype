#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> //NOTE: なんか#include エラーが出るが動くので無視した
#include <glad/glad.h>
#include "config.h"

//OFFLINE NOTE: 名前空間のxmlコメントはファイルごとに買いてもいいのか？
/// @brief ウィンドウ管理など、ゲームのコアロジック関数を格納する名前空間
namespace core
{
static const int WINDOW_WIDTH = 1200;
static const int WINDOW_HEIGHT = 800;

class Window
{
public:
  Window() = default;
  ~Window() = default;

  /// @brief GLFWの初期化、OpenGLの設定、ウィンドウの作成、GLADの初期化、コンテキストの生成。
  /// @return エラーが発生したら-1を返す。
  int CreateWindow();

  /// @brief フレームバッファのクリア
  void ClearBuffer();

  /// @brief フレームバッファの切り替え（ダブルバッファシステム）
  void SwapBuffers();

  //OFFLINENOTE: これはなに？
  /// @brief glfwPollEvents()のラッパー関数
  void PollEvents();

  /// @brief glfwWindowShouldClose()のラッパー関数
  /// @return ゲームループを終了するべきかどうか
  bool WindowShouldClose();

  /// @brief glfwTerminate()のラッパー関数
  void TerminateWindow();

private:
  /// @brief glfwのエラーハンドルシステムにセットするコールバック関数
  /// @param error 
  /// @param description 
  void errorCallback(int error, const char *description);

  GLFWwindow *window_;
};
}