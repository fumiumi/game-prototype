#define GL_SILENCE_DEPRECATION //OFFLINENOTE: お前は何者？
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <string>

#include "config.h"
#include "./game/game.h"

// // シェーダーのテスト用
// #include "engine/renderer/shader/Shader.h"
// #include "engine/renderer/shader/Mesh.h"

// std::string TRIANGLE_VERT_PATH = static_cast<std::string>(PROJECT_PATH)  + "/shaders/triangle/TriangleVertex.glsl";
// std::string TRIANGLE_FRAG_PATH = static_cast<std::string>(PROJECT_PATH)  + "/shaders/triangle/TriangleFragment.glsl";

int main()
{

  // // --- シェーダーのコンパイル ---
  // Shader vertexShader(TRIANGLE_VERT_PATH, GL_VERTEX_SHADER);     // 頂点シェーダー
  // Shader fragmentShader(TRIANGLE_FRAG_PATH, GL_FRAGMENT_SHADER); // フラグメントシェーダー

  // // シェーダーオブジェクトをプログラムにリンク
  // GLuint programID = glCreateProgram();
  // glAttachShader(programID, vertexShader.GetID());
  // glAttachShader(programID, fragmentShader.GetID());
  // glLinkProgram(programID);

  // // リンクエラーのチェック
  // GLint linkSuccess = 0;
  // glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
  // if (!linkSuccess)
  // {
  //   GLint logLength = 0;
  //   glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
  //   std::string programLog(logLength, '\0');
  //   glGetProgramInfoLog(programID, logLength, nullptr, &programLog[0]);
  //   std::cerr << "Program linking failed:\n"
  //             << programLog << std::endl;
  //   glfwDestroyWindow(window);
  //   glfwTerminate();
  //   return -1;
  // }

  // // 頂点データ
  // std::vector<Vertex> vertices = {
  //     // x,    y,    z,     nx,   ny,   nz,    u, v
  //     {-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0, 0},
  //     {0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0, 0},
  //     {0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0, 0}};
  // // インデックスは使用しないので空のままとする
  // std::vector<unsigned int> indices;

  // Mesh triangleMesh(vertices, indices);

  // メインループ
  Game *game = new Game();
  game->Run();

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