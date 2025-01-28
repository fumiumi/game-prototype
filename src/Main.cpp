#include <iostream>
#include <GLFW/glfw3.h> // GLFWのヘッダ

#include "Game.h"

// ウィンドウのサイズ
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

// エラコールバック（任意）
void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "[GLFW Error] Code: " << error << ", Description: " << description << std::endl;
}

int main()
{
    // GLFW初期化
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }

// Vulkanに移行する
//     // OpenGLバージョン指定 (例: 3.3 Core)
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #if __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

    // ウィンドウ作成
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game-prototype", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 垂直同期の設定（任意）
    glfwSwapInterval(1);

    // ビューポート設定
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 背景色（クリアカラー）
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

    // ゲームインスタンスを生成
    Game game;
    game.Initialize();

    // メインループ
    while (!glfwWindowShouldClose(window))
    {
        // 入力処理
        glfwPollEvents();

        // 更新処理
        game.Update();

        // 描画処理
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        // バッファを入れ替え
        glfwSwapBuffers(window);
    }

    // 終了処理
    game.Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
