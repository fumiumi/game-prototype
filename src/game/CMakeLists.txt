# src/game/CMakeLists.txt

project(Game)  # プロジェクト名をGameに設定
add_executable(GameExe 
    game.cpp 
 )
 
target_link_libraries(GameExe PRIVATE EngineLib)
