#version 410 core // macOSでは410が最大

layout(location=0)in vec3 aPos;// 頂点の位置
layout(location=1)in vec3 aColor;// 頂点ごとの色

out vec3 vertexColor;// フラグメントシェーダーに渡す色

void main()
{
  gl_Position=vec4(aPos,1.);// アフィン変換をするためにvec4に変換
  vertexColor=aColor;// フラグメントシェーダーに渡す
}
