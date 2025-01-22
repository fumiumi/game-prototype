#pragma once

#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include "components/Component.h"

class Entity
{
public:
    explicit Entity(const std::string& name)
        : m_name(name) {}

    ~Entity() = default;

    // コンポーネントを追加するテンプレートメソッド
    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        // 生成して動的に保持
        auto comp = std::make_unique<T>(std::forward<TArgs>(args)...);
        comp->m_owner = this; // 所有エンティティを知らせる
        T& ref = *comp;       // 返却用への参照を控えておく

        m_components.push_back(std::move(comp));
        return ref;
    }

    // 全てのコンポーネントをUpdate
    void Update()
    {
        for (auto& comp : m_components)
        {
            comp->Update();
        }
    }

    // (必要なら) Render呼び出しや、各コンポーネント固有の処理もここから行う

    const std::string& GetName() const { return m_name; }

private:
    std::string m_name;

    // Componentの所有リスト
    std::vector<std::unique_ptr<Component>> m_components;
};
