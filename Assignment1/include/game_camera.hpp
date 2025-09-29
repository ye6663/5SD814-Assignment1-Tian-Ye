// game_camera.hpp

#pragma once
#include <raylib.h>

class GameCamera
{
public:
    void initialize(Vector2 position, Vector2 extent);
    void update();
    
    void setPosition(Vector2 position) { m_position = position; }
    Vector2 getPosition() const { return m_position; }
    
    Rectangle getFrustum() const { return m_frustum; }
    
    void renderDebug() const;
    
private:
    Vector2 m_position = {0, 0};
    Vector2 m_extent = {0, 0};
    Rectangle m_frustum = {0, 0, 0, 0};
};