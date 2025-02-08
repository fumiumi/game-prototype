add_library(engine_renderer_shader
  Shader.cpp
  # ShaderManager.cpp
  Mesh.cpp
  # VertexArray.cpp
  # VertexBuffer.cpp
)

target_include_directories(engine_renderer_shader PRIVATE
  ${PROJECT_SOURCE_DIR}/extern/glad/include
)