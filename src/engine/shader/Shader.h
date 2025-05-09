#pragma once

#include <string>
#include <stdexcept>
#include <glad/glad.h>

/// @brief OpenGLシェーダーを表すクラス (コンパイル済み)
///        ShaderManagerによって管理されることを想定
class Shader
{
public:
    /// @brief コンストラクタ
    /// @param filePath GLSLソースファイルのパス
    /// @param type プログラマブルシェーダータイプ
    /// @throws std::runtime_error
    Shader(const std::string& filePath, GLenum type);

    ~Shader();

    /// @brief シェーダーオブジェクトIDを取得 (glCreateShader で作られたID)
    GLuint GetID() const { return shaderID; }

    /// @brief シェーダータイプ (例: GL_VERTEX_SHADER) を取得
    GLenum GetType() const { return shaderType; }

    /// @brief ソースコードを再読み込み・再コンパイルする (オプション)
    /// @throws std::runtime_error コンパイル失敗時
    void Reload();

private:
    GLuint shaderID;
    GLenum shaderType;
    std::string filePath; // ファイルパスを保持し、Reload時に再利用

    std::string ReadFile(const std::string& filePath) const;
    void CompileShader(const std::string& source);

    // OpenGLログ取得用
    std::string GetCompileLog() const;
};

