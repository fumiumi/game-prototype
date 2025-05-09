# src/game/CMakeLists.txt

project(game)  # プロジェクト名をGameに設定
add_library(game 
    game.cpp 
 )

# エンジンライブラリをリンク
# これにより、ゲームエンジンを使用することができる
target_link_libraries(game PRIVATE engine)