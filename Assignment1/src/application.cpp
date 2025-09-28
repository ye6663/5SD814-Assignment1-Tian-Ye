// application.cpp

#include "application.hpp"
#include "math_utils.hpp"
#include <raylib.h>
#include <iostream>
#include <algorithm>

bool Application::initialize()
{
    // ��ʼ���������� (10x10����ÿ��1000x1000����)
    m_grid.initialize(10, 10, 1000, 1000);

    // ����6000��С����
    m_grid.generateAsteroids(6000);
    m_totalAsteroids = 6000;

    // ��ʼ���ǿ�
    m_starfield.initialize(m_width, m_height);

    std::cout << "Application initialized successfully" << std::endl;
    return true;
}

void Application::shutdown()
{
    // ������Դ
}

void Application::update()
{
    processInput();

    // ����С������ת
    m_grid.updateAsteroids();

    // �ռ���Ⱦ����
    collectRenderCommands();
}

void Application::processInput()
{
    // �л�������ʾ
    if (IsKeyPressed(KEY_F1)) m_showDebug = !m_showDebug;
}

void Application::collectRenderCommands()
{
    m_renderCommands.clear();
    m_visibleAsteroids = 0;

    auto visibleAsteroids = m_grid.getVisibleAsteroids({});
    m_visibleAsteroids = (int)visibleAsteroids.size();

    // ���С���ǵ���Ⱦ����
    for (const auto& asteroid : visibleAsteroids)
    {
        RenderCommand cmd;
        cmd.type = RenderCommandType::Asteroid;
        cmd.position = asteroid.position;
        cmd.rotation = asteroid.rotation;
        cmd.size = asteroid.size;
        cmd.color = asteroid.color;
        cmd.layer = asteroid.layer; // ���ݴ�С���ò㼶

        m_renderCommands.push_back(cmd);
    }

    // ���㼶������Ⱦ����
    std::sort(m_renderCommands.begin(), m_renderCommands.end(),
        [](const RenderCommand& a, const RenderCommand& b) {
            return a.layer < b.layer;
        });
}

void Application::render()
{
    // ִ����������Ⱦ����
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

    // ��Ⱦ������Ϣ
    if (m_showDebug)
    {
        renderDebugInfo();
    }
}

void Application::renderDebugInfo()
{
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, GREEN);
    DrawText(TextFormat("Visible: %d/%d", m_visibleAsteroids, m_totalAsteroids), 10, 40, 20, GREEN);

    // ��ʾ������ʾ
    DrawText("Controls: W - Thrust, A/D - Rotate, F1 - Toggle Debug", 10, m_height - 30, 20, GRAY);
}