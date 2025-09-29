// game_camera.cpp

#include "game_camera.hpp"
#include <raylib.h>

void GameCamera::initialize(Vector2 position, Vector2 extent)
{
    m_position = position;
    m_extent = extent;
    update();
}

void GameCamera::update()
{
    m_frustum.x = m_position.x - m_extent.x;
    m_frustum.y = m_position.y - m_extent.y;
    m_frustum.width = m_extent.x * 2.0f;
    m_frustum.height = m_extent.y * 2.0f;
}

void GameCamera::renderDebug() const
{
    DrawRectangleLinesEx(m_frustum, 2.0f, RED);
}