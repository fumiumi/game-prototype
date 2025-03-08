#include "window.h"

namespace core
{
int Window::CreateWindow()
{
  //OFFLINENOTE: TODO: ロガーシステムに差し替える
  glfwSetErrorCallback(errorCallback);

  // GLFWの初期化
  if (!glfwInit())
  {
    //OFFLINENOTE: TODO: ロガーシステムに差し替える
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // OpenGLのバージョン指定
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  // ウィンドウの生成
  window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game-prototype", NULL, NULL);
  if (window_ == nullptr)
  {
    //OFFLINENOTE: TODO: ロガーシステムに差し替える
    std::cerr << "Failed to create window" << std::endl;
    TerminateWindow()
    return -1;
  }
  
  // コンテキストの生成
  glfwMakeContextCurrent(window);
  
  // GLADの初期化
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    //OFFLINENOTE: TODO: ロガーシステムに差し替える
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  
  // ビューポートの設定
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  
  // 画面のクリア色を設定
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  // リンクエラーのチェック
  // OFFLINENOTE: これいる？
  GLint linkSuccess = 0;
  glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
  if (!linkSuccess)
  {
    GLint logLength = 0;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
    std::string programLog(logLength, '\0');
    glGetProgramInfoLog(programID, logLength, nullptr, &programLog[0]);
    std::cerr << "Program linking failed:\n"
    << programLog << std::endl;
    glfwDestroyWindow(window);
    TerminateWindow()
    return -1;
  } 
}

void Window::ClearBuffer()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
  if(window_ == nullptr)
  {
    return;
  }

  glfwSwapBuffers(window_);
}

void Window::PollEvents()
{
  glfwPollEvents();
}

bool Window::WindowShouldClose()
{
  return glfwWindowShouldClose(window_)
}

void Window::TerminateWindow()
{
  glfwTerminate();
}

void Window::errorCallback(int error, const char *description)
{
  std::cerr << "GLFW Error: " << description << std::endl;
}
} //namespace core
