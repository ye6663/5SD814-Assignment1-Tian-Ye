// player.cpp

#include "player.hpp"
#include <raylib.h>
#include <cmath>

void Player::initialize(Vector2 position)
{
    m_position = position;
    m_rotation = 0;
    m_velocity = { 0, 0 };
}

void Player::update()
{
    // 应用阻力
    m_velocity.x *= DRAG;
    m_velocity.y *= DRAG;

    // 限制最大速度
    float speed = sqrtf(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (speed > MAX_SPEED)
    {
        m_velocity.x = m_velocity.x / speed * MAX_SPEED;
        m_velocity.y = m_velocity.y / speed * MAX_SPEED;
    }

    // 更新位置
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;
}

void Player::applyThrust()
{
    m_velocity.x += cosf(m_rotation) * THRUST_FORCE;
    m_velocity.y += sinf(m_rotation) * THRUST_FORCE;
}

void Player::rotateLeft()
{
    m_rotation -= ROTATION_SPEED * GetFrameTime();
}

void Player::rotateRight()
{
    m_rotation += ROTATION_SPEED * GetFrameTime();
}