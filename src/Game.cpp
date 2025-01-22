#include "Game.h"
#include <iostream>
#include "components/TransformComponent.h"

void Game::Initialize()
{
    // 例: プレイヤーのEntityを生成して、コンポーネントを追加
    auto player = std::make_unique<Entity>("Player");
    player->AddComponent<TransformComponent>(0.0f, 0.0f);

    // 他のコンポーネントを追加する場合はここで…

    m_entities.push_back(std::move(player));

    std::cout << "Game Initialized.\n";
}

void Game::Update()
{
    // 全エンティティのUpdateを呼ぶ
    for (auto& entity : m_entities)
    {
        entity->Update();
    }
}

void Game::Render()
{
    // ここでOpenGLの描画呼び出し or 各エンティティの描画ロジックを実行
    // 例: EntityにRender()を持たせる場合は entity->Render(); など
}

void Game::Shutdown()
{
    // ゲーム終了時のリソース解放など
    m_entities.clear();
    std::cout << "Game Shutdown.\n";
}
