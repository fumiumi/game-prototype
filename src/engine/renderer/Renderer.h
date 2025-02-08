#pragma once
#include <memory>

class Mesh;
class Material;

struct Renderable {
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    Transform transform;  // 位置、回転、スケールなど
};

class Renderer {
public:
    void Submit(const Renderable& renderable) {
        // レンダリングキューに追加
    }

    void Render() {
        // 各レンダブルオブジェクトに対して描画呼び出し
        // シェーダーを有効にして、VAOをバインドし、glDrawArrays/glDrawElements を呼ぶ
    }
};