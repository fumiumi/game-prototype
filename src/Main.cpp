#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

// #include "Game.h"

// ウィンドウのサイズ
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

// エラコールバック（任意）
void glfwErrorCallback(int error, const char *description)
{
    std::cerr << "[GLFW Error] Code: " << error << ", Description: " << description << std::endl;
}

int main()
{
    //-----------------------------------------------------------------------------------
    // Vulkanの動作確認
    // 利用可能なレイヤーの数を取得
    uint32_t layerCount = 0;
    VkResult result = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to enumerate Vulkan layers!" << std::endl;
        return -1;
    }

    // レイヤー情報を取得
    std::vector<VkLayerProperties> layers(layerCount);
    result = vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to get Vulkan layer properties!" << std::endl;
        return -1;
    }

    // Vulkan が正しくリンクされているかを確認
    std::cout << "Vulkan is successfully linked!" << std::endl;
    std::cout << "Available Vulkan Layers:" << std::endl;

    for (const auto &layer : layers)
    {
        std::cout << " - " << layer.layerName << std::endl;
    }
    //-----------------------------------------------------------------------------------

    // エラーコールバックを設定
    glfwSetErrorCallback(glfwErrorCallback);

    // GLFW初期化
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }

    // #if __APPLE__
    //     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // #endif

    // ウィンドウヒント設定
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // ウィンドウ作成
    GLFWwindow *window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        "game-prototype",
        nullptr,
        nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
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
    // Game game;
    // game.Initialize();

    // メインループ
    while (!glfwWindowShouldClose(window))
    {
        // 入力処理
        glfwPollEvents();

        // // 更新処理
        // game.Update();

        // // 描画処理
        glClear(GL_COLOR_BUFFER_BIT);
        // game.Render();

        // バッファを入れ替え
        glfwSwapBuffers(window);
    }

    // 終了処理
    // game.Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
