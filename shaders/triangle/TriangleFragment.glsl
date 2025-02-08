#version 410 core // macOSでは410が最大

in vec3 vertexColor;// 頂点シェーダーから受け取る色
out vec4 FragColor;// 出力する色

void main()
{
  FragColor=vec4(vertexColor,1.);// RGBにアルファ値を加えて出力
}
