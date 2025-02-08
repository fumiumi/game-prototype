#include "Mesh.h"
#include <stdexcept>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices = {})
    : m_vertices(vertices), m_indices(indices)
{
  SetupMesh();
}

Mesh::~Mesh()
{
  // OpenGLリソースの解放
  if (EBO != 0)
  {
    glDeleteBuffers(1, &EBO);
    EBO = 0;
  }
  if (VBO != 0)
  {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }
  if (VAO != 0)
  {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
  }
}

void Mesh::SetupMesh()
{
  // 1. VAOの生成
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // 2. VBOの生成と頂点データのバッファリング
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,
               m_vertices.size() * sizeof(Vertex),
               m_vertices.data(),
               GL_STATIC_DRAW);

  // 3. EBO (インデックスバッファ) がある場合
  if (!m_indices.empty())
  {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(unsigned int),
                 m_indices.data(),
                 GL_STATIC_DRAW);
  }

  // 4. 頂点属性を設定 (位置, 法線, UVなど)
  //   例: Vertex のメンバ構造 {x, y, z, nx, ny, nz, u, v}
  //   → 位置属性 (location=0), 法線属性 (location=1), UV (location=2) など
  //   実際の構造にあわせて設定してください

  // 位置属性 (layout = 0)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void *)0);

  // 法線属性 (layout = 1)
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void *)offsetof(Vertex, nx) // 構造体のnxの位置
  );

  // UV属性 (layout = 2)
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
      2,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void *)offsetof(Vertex, u) // 構造体のuの位置
  );

  // VAOを解除
  glBindVertexArray(0);
}

void Mesh::Draw() const
{
  // VAOをバインドして描画
  glBindVertexArray(VAO);
  if (!m_indices.empty())
  {
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
  }
  else
  {
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices.size()));
  }
  glBindVertexArray(0);
}
