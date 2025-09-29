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

    // ��ʼ�����
    m_player.initialize({ m_width / 2.0f, m_height / 2.0f });

    // ��ʼ�����
    m_camera.initialize({ m_width / 2.0f, m_height / 2.0f },
        { m_width / 2.0f, m_height / 2.0f });

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

    // �������
    m_player.update();

    // ��������������
    updateCamera();
    m_camera.update();

    // ����С������ת
    m_grid.updateAsteroids();

    // �ռ���Ⱦ����
    collectRenderCommands();
}

void Application::processInput()
{
    // ��ҿ���
    if (IsKeyDown(KEY_W)) m_player.applyThrust();
    if (IsKeyDown(KEY_A)) m_player.rotateLeft();
    if (IsKeyDown(KEY_D)) m_player.rotateRight();

    // �л�������ʾ
    if (IsKeyPressed(KEY_F1)) m_showDebug = !m_showDebug;
}

void Application::updateCamera()
{
    // ���������ң�����ƽ������
    Vector2 targetPos = m_player.getPosition();
    Vector2 currentPos = m_camera.getPosition();

    Vector2 newPos = {
        MathUtils::lerp(currentPos.x, targetPos.x, 0.1f),
        MathUtils::lerp(currentPos.y, targetPos.y, 0.1f)
    };

    m_camera.setPosition(newPos);
}

void Application::collectRenderCommands()
{
    m_renderCommands.clear();
    m_visibleAsteroids = 0;

    // ����ǿյ���Ⱦ���� (������)
    m_starfield.addRenderCommands(m_renderCommands, m_camera);

    // ��ȡ�ɼ������С����
    Rectangle frustum = m_camera.getFrustum();
    auto visibleAsteroids = m_grid.getVisibleAsteroids(frustum);
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

    // �����ҵ���Ⱦ���� (���ϲ�)
    RenderCommand playerCmd;
    playerCmd.type = RenderCommandType::Player;
    playerCmd.position = m_player.getPosition();
    playerCmd.rotation = m_player.getRotation();
    playerCmd.size = { 20, 20 };
    playerCmd.color = WHITE;
    playerCmd.layer = 10; // ��߲�

    m_renderCommands.push_back(playerCmd);

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

        case RenderCommandType::Player:
            // ���������α�ʾ�ɴ�
            Vector2 front = {
                cmd.position.x + cosf(cmd.rotation) * cmd.size.x,
                cmd.position.y + sinf(cmd.rotation) * cmd.size.y
            };
            Vector2 left = {
                cmd.position.x + cosf(cmd.rotation + 2.5f) * cmd.size.x * 0.6f,
                cmd.position.y + sinf(cmd.rotation + 2.5f) * cmd.size.y * 0.6f
            };
            Vector2 right = {
                cmd.position.x + cosf(cmd.rotation - 2.5f) * cmd.size.x * 0.6f,
                cmd.position.y + sinf(cmd.rotation - 2.5f) * cmd.size.y * 0.6f
            };

            DrawTriangle(front, left, right, cmd.color);
            break;
        }
    }

    // ��Ⱦ������Ϣ
    if (m_showDebug)
    {
        renderDebugInfo();
        m_grid.renderDebug(m_camera);
        m_camera.renderDebug();
    }
}

void Application::renderDebugInfo()
{
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, GREEN);
    DrawText(TextFormat("Visible: %d/%d", m_visibleAsteroids, m_totalAsteroids), 10, 40, 20, GREEN);
    DrawText(TextFormat("Position: (%.1f, %.1f)",
        m_player.getPosition().x,
        m_player.getPosition().y), 10, 70, 20, GREEN);

    // ��ʾ������ʾ
    DrawText("Controls: W - Thrust, A/D - Rotate, F1 - Toggle Debug", 10, m_height - 30, 20, GRAY);
}