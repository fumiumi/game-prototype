#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> //NOTE: なんか#include エラーが出るが動くので無視した
#include <glad/glad.h>
// #include <AL/al.h>
// #include <AL/alc.h>
// #include <AL/alext.h>
// #include <Box2D/Box2D.h>
// #include <freetype/freetype.h>
// #include <nlohmann/json.hpp>
#include <stb_image.h>
#include "config.h"

const char *filename = "../extern/assets/sample.png";

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

// stb_image.hのテスト
GLuint loadTexture(const char *filename)
{
  int width, height, channels;
  unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
  if (data == nullptr)
  {
    std::cerr << "Failed to load image file: " << filename << std::endl;
    return 0;
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  
  stbi_image_free(data);

  return texture;
}

//NOTE: エントリポイントは"Main"ではなく"main"であることに注意
int main()
{
  glfwSetErrorCallback(errorCallback);

  // GLFWの初期化
  if (!glfwInit())
  {
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
  GLFWwindow *window = glfwCreateWindow(1200, 800, "test-opengl-biome", NULL, NULL);
  if(window == nullptr) 
  {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // コンテキストの生成
  glfwMakeContextCurrent(window);

      // GLADの初期化
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 画面のクリア色を設定
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // メインループ
  while (!glfwWindowShouldClose(window))
  {
    // バッファのクリア
    glClear(GL_COLOR_BUFFER_BIT);

    // バッファの入れ替え
    glfwSwapBuffers(window);

    // イベントのポーリング
    glfwPollEvents();
  }

  // GLFWの終了処理
  glfwTerminate();

  return 0;
}
