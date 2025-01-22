#pragma once
#include "Component.h"

class TransformComponent : public Component
{
public:
    TransformComponent(float x, float y)
        : m_x(x), m_y(y) {}

    void Update() override;

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }

    void SetPosition(float x, float y) { m_x = x; m_y = y; }

private:
    float m_x;
    float m_y;
};
