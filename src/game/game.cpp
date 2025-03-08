#include "game.h"

Game::Run()
{
  core::Window window_system = new core::Window();

  window_system.CreateWindow();

  while(!window_system.WindowShouldClose())
  {
    window_system.ClearBuffer();

    window_system.SwapBuffers();

    window_system.PollEvents();
  }

  window_system.TerminateWindow();
}
