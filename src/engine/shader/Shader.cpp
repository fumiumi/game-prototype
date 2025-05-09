#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &filePath, GLenum type)
  : shaderID(0),
    shaderType(type),
    filePath(filePath)
{
  // シェーダーIDを生成
  shaderID = glCreateShader(shaderType);
  if (shaderID == 0)
  {
    throw std::runtime_error("Failed to create shader object.");
  }

  // ファイルからソースコードを読み込み
  std::string source = ReadFile(filePath);
  // コンパイル実行
  CompileShader(source);
}

Shader::~Shader()
{
  // シェーダーが有効ならOpenGLリソースを削除
  if (shaderID != 0)
  {
    glDeleteShader(shaderID);
    shaderID = 0;
  }
}

void Shader::Reload()
{
  // 現在のシェーダーを一旦削除
  if (shaderID != 0)
  {
    glDeleteShader(shaderID);
  }

  // 新たにシェーダーを生成
  shaderID = glCreateShader(shaderType);
  if (shaderID == 0)
  {
    throw std::runtime_error("Failed to create shader object (reload).");
  }

  // ファイルから再読み込み
  std::string source = ReadFile(filePath);
  CompileShader(source);
}

std::string Shader::ReadFile(const std::string &filePath) const
{
  std::ifstream fileStream(filePath, std::ios::in | std::ios::binary);
  if (!fileStream.is_open())
  {
    throw std::runtime_error("Shader file not found: " + filePath);
  }

  std::stringstream buffer;
  buffer << fileStream.rdbuf();
  return buffer.str();
}

void Shader::CompileShader(const std::string &source)
{
  const char *src = source.c_str();
  glShaderSource(shaderID, 1, &src, nullptr);
  glCompileShader(shaderID);

  // コンパイル結果をチェック
  GLint success = 0;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    std::string log = GetCompileLog();
    throw std::runtime_error("Shader compilation failed (" + filePath + "):\n" + log);
  }
}

std::string Shader::GetCompileLog() const
{
  GLint length = 0;
  glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
  if (length > 1)
  {
    std::string log(length, '\0');
    glGetShaderInfoLog(shaderID, length, nullptr, &log[0]);
    return log;
  }
  return {};
}
