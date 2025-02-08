#pragma once
#include <memory>

class Shader; // 前方宣言

class ShaderManager
{
public:
  static ShaderManager &GetInstance()
  {
    static ShaderManager instance;
    return instance;
  }

  std::shared_ptr<Shader> LoadShader(
      const std::string &name,
      const std::string &vertexPath,
      const std::string &fragmentPath);
  // ... 他のメソッド

private:
  // コンストラクタ
  ShaderManager() {}
  // コピー禁止
  ShaderManager(const ShaderManager &) = delete;
  ShaderManager &operator=(const ShaderManager &) = delete;
  // ムーブ禁止
  ShaderManager(ShaderManager &&) = delete;
  ShaderManager &operator=(ShaderManager &&) = delete;
};