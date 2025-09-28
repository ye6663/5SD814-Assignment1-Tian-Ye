// main.cpp

#include "application.hpp"
#include <raylib.h>

int main(int argc, char** argv)
{
    // 设置窗口大小为1280x720
    InitWindow(1280, 720, "Asteroid Field Renderer");
    SetTargetFPS(60);

    Application app;
    if (!app.initialize())
    {
        CloseWindow();
        return -1;
    }

    // 主循环
    while (!WindowShouldClose())
    {
        app.update();

        BeginDrawing();
        ClearBackground(BLACK);
        app.render();
        EndDrawing();
    }

    app.shutdown();
    CloseWindow();

    return 0;
}