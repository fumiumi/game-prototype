# src/engine/CMakeLists.txt

# プロジェクト名: ビルドシステム全体の識別用であり、target_link_libraries() とは無関係
project(engine)  

# add_subdirectory(actor)
# add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(renderer)
# add_subdirectory(scripting)
add_subdirectory(shader)
# add_subdirectory(sound)
# add_subdirectory(utils)

target_link_libraries(engine PRIVATE engine_core)
