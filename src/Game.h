#pragma once

#include <vector>
#include <memory>

#include "Entity.h"

class Game
{
public:
    Game() = default;
    ~Game() = default;

    // ゲーム起動時の初期化処理
    void Initialize();

    // メインループ内で呼び出す
    void Update();
    void Render();

    // 終了時のクリーンアップ
    void Shutdown();

private:
    // 例: ゲーム内に存在するエンティティのリスト
    std::vector<std::unique_ptr<Entity>> m_entities;
};
