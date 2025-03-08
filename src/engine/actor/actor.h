#pragma once

#include <vector>

#include "../components/component.h"

class Actor
{
public:
  Actor();
  ~Actor();

  void Update() = 0;

private:
  // ほとんどのゲームオブジェクトに必要な最低限のメンバ変数
  double x_, y_;
  double vx_, vy_;
  std::vector<Component> components_
}