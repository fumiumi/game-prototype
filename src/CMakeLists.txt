# src/CMakeLists.txt
project(source)  # プロジェクト名をGameに設定
add_subdirectory(engine)  # エンジン（ライブラリ）
add_subdirectory(game)    # ゲーム（実行ファイル）
taeget_link_libraries(source PRIVATE )