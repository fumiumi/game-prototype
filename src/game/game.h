#pragma once
#include "../engine/core/window.h"

/// @brief クライアント向けのゲームクラス
class Game
{
public:
  Game() = default;
  ~Game() = default;

  void Run();
};