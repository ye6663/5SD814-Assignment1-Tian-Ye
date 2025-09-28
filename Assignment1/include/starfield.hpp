#pragma once
#include "render_command.hpp"
#include <vector>

class Starfield
{
public:
    void initialize(int screenWidth, int screenHeight);
    void addRenderCommands(std::vector<RenderCommand>& commands);
    
private:
    static const int STAR_COUNT = 1000;
    
    struct Star
    {
        Vector2 position;
        float size;
        Color color;
        float parallaxFactor; // 视差因子，用于创建深度感
    };
    
    std::vector<Star> m_stars;
    int m_screenWidth = 0;
    int m_screenHeight = 0;
};