// application.cpp

#include "application.hpp"
#include "math_utils.hpp"
#include <raylib.h>
#include <iostream>
#include <algorithm>

bool Application::initialize()
{
    // 初始化网格世界 (10x10区域，每个1000x1000像素)
    m_grid.initialize(10, 10, 1000, 1000);

    // 生成6000个小行星
    m_grid.generateAsteroids(6000);
    m_totalAsteroids = 6000;

    // 初始化星空
    m_starfield.initialize(m_width, m_height);

    std::cout << "Application initialized successfully" << std::endl;
    return true;
}

void Application::shutdown()
{
    // 清理资源
}

void Application::update()
{
    processInput();

    // 更新小行星旋转
    m_grid.updateAsteroids();

    // 收集渲染命令
    collectRenderCommands();
}

void Application::processInput()
{
    // 切换调试显示
    if (IsKeyPressed(KEY_F1)) m_showDebug = !m_showDebug;
}

void Application::collectRenderCommands()
{
    m_renderCommands.clear();
    m_visibleAsteroids = 0;

    auto visibleAsteroids = m_grid.getVisibleAsteroids({});
    m_visibleAsteroids = (int)visibleAsteroids.size();

    // 添加小行星到渲染队列
    for (const auto& asteroid : visibleAsteroids)
    {
        RenderCommand cmd;
        cmd.type = RenderCommandType::Asteroid;
        cmd.position = asteroid.position;
        cmd.rotation = asteroid.rotation;
        cmd.size = asteroid.size;
        cmd.color = asteroid.color;
        cmd.layer = asteroid.layer; // 根据大小设置层级

        m_renderCommands.push_back(cmd);
    }

    // 按层级排序渲染命令
    std::sort(m_renderCommands.begin(), m_renderCommands.end(),
        [](const RenderCommand& a, const RenderCommand& b) {
            return a.layer < b.layer;
        });
}

void Application::render()
{
    // 执行排序后的渲染命令
    for (const auto& cmd : m_renderCommands)
    {
        switch (cmd.type)
        {
        case RenderCommandType::Star:
            DrawRectanglePro(
                Rectangle{ cmd.position.x, cmd.position.y, cmd.size.x, cmd.size.y },
                { cmd.size.x / 2, cmd.size.y / 2 },
                cmd.rotation,
                cmd.color
            );
            break;

        case RenderCommandType::Asteroid:
            DrawRectanglePro(
                Rectangle{ cmd.position.x, cmd.position.y, cmd.size.x, cmd.size.y },
                { cmd.size.x / 2, cmd.size.y / 2 },
                cmd.rotation,
                cmd.color
            );
            break;
        }
    }

    // 渲染调试信息
    if (m_showDebug)
    {
        renderDebugInfo();
    }
}

void Application::renderDebugInfo()
{
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, GREEN);
    DrawText(TextFormat("Visible: %d/%d", m_visibleAsteroids, m_totalAsteroids), 10, 40, 20, GREEN);

    // 显示控制提示
    DrawText("Controls: W - Thrust, A/D - Rotate, F1 - Toggle Debug", 10, m_height - 30, 20, GRAY);
}