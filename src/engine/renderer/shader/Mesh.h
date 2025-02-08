#pragma once
#include <vector>
#include <glad/glad.h>

// 頂点構造の例（位置・法線・UVなど）
struct Vertex {
    // Position
    float x, y, z;
    // Normal (必要に応じて)
    float nx, ny, nz;
    // TexCoords (必要に応じて)
    float u, v;
};

/// @brief 頂点データをGPUにアップロードし、VAO/VBOを管理するクラス
class Mesh
{
public:
    /// @param vertices 頂点配列
    /// @param indices  インデックス配列(利用しないなら空でもOK)
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    // 実際の描画を行う
    void Draw() const;

    // 必要に応じて、頂点バッファを再作成・更新したりできるようにする
    // void UpdateBuffers(const std::vector<Vertex>& newVertices, ...);

private:
    // GPUハンドル
    GLuint VAO {0};
    GLuint VBO {0};
    GLuint EBO {0}; // エレメントバッファ, インデックス描画が必要な場合のみ

    // データを保存するかどうかは用途次第
    // 頂点を保持しておきたいならメンバに入れる
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    // バッファ生成/初期化のヘルパー
    void SetupMesh();
};
