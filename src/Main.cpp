#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> //NOTE: なんか#include エラーが出るが動くので無視した
#include <glad/glad.h>
#include <vector>
#include <string>
#include "config.h"

// シェーダーのテスト用
#include "engine/renderer/shader/Shader.h"
#include "engine/renderer/shader/Mesh.h"

static const int WINDOW_WIDTH = 1200;
static const int WINDOW_HEIGHT = 800;

std::string TRIANGLE_VERT_PATH = "/Users/kawaguchibunnari/git/game-prototype/shaders/triangle/TriangleVertex.glsl";
std::string TRIANGLE_FRAG_PATH = "/Users/kawaguchibunnari/git/game-prototype/shaders/triangle/TriangleFragment.glsl";

void errorCallback(int error, const char *description)
{
  std::cerr << "GLFW Error: " << description << std::endl;
}

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
  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game-prototype", NULL, NULL);
  if (window == nullptr)
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

  // ビューポートの設定
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  // 画面のクリア色を設定
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  // --- シェーダーのコンパイル ---
  Shader vertexShader(TRIANGLE_VERT_PATH, GL_VERTEX_SHADER);     // 頂点シェーダー
  Shader fragmentShader(TRIANGLE_FRAG_PATH, GL_FRAGMENT_SHADER); // フラグメントシェーダー

  // シェーダーオブジェクトをプログラムにリンク
  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertexShader.GetID());
  glAttachShader(programID, fragmentShader.GetID());
  glLinkProgram(programID);

  // リンクエラーのチェック
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
    glfwTerminate();
    return -1;
  }


  // 頂点データ
  std::vector<Vertex> vertices = {
      // x,    y,    z,    nx, ny, nz,   u, v
      {-0.5f, -0.5f, 0.0f, 0, 0, 0, 0, 0},
      {0.5f, -0.5f, 0.0f, 0, 0, 0, 0, 0},
      {0.0f, 0.5f, 0.0f, 0, 0, 0, 0, 0}};
  // インデックスは使用しないので空のままとする
  std::vector<unsigned int> indices;

  Mesh triangleMesh(vertices, indices);

  // メインループ
  while (!glfwWindowShouldClose(window))
  {
    // バッファのクリア
    glClear(GL_COLOR_BUFFER_BIT);

    // シェーダープログラムを使用
    glUseProgram(programID);

    // メッシュの描画 (Mesh::Draw 内で VAO をバインドして描画)
    triangleMesh.Draw();

    // バッファの入れ替え
    glfwSwapBuffers(window);

    // イベントのポーリング
    glfwPollEvents();
  }

  // GLFWの終了処理
  glfwTerminate();

  return 0;
}

// // stb_image.hのテスト
// GLuint loadTexture(const char *filename)
// {
//   int width, height, channels;
//   unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
//   if (data == nullptr)
//   {
//     std::cerr << "Failed to load image file: " << filename << std::endl;
//     return 0;
//   }

//   GLuint texture;
//   glGenTextures(1, &texture);
//   glBindTexture(GL_TEXTURE_2D, texture);
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

//   stbi_image_free(data);

//   return texture;
// }