#pragma once
#include "../engine/core/window.h"

//OFFLINENOTE: これクラスにする必要あるかな？
class Game
{
public:
  Game() = default;
  ~Game() = default;

  void Run();
};