#pragma once

class Entity; // 前方宣言

class Component
{
public:
    virtual ~Component() = default;

    virtual void Update() {}
    // virtual void Render() {} // 必要なら追加

protected:
    // 自分を持っているEntity (AddComponent時にセット)
    Entity* m_owner = nullptr;
};
