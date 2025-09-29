// starfield.cpp

#include "starfield.hpp"
#include "math_utils.hpp"
#include <raylib.h>

void Starfield::initialize(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    m_stars.resize(STAR_COUNT);

    for (auto& star : m_stars)
    {
        // 随机位置 (在屏幕外扩展区域)
        star.position = {
            MathUtils::random(-(float)screenWidth, (float)screenWidth * 2),
            MathUtils::random(-(float)screenHeight, (float)screenHeight * 2)
        };

        // 随机大小和颜色
        star.size = MathUtils::random(1.0f, 3.0f);

        unsigned char brightness = (unsigned char)MathUtils::random(100, 255);
        star.color = { brightness, brightness, brightness, 255 };

        // 随机视差因子 (0.1-0.9)
        star.parallaxFactor = MathUtils::random(0.1f, 0.9f);
    }
}

void Starfield::addRenderCommands(std::vector<RenderCommand>& commands, const GameCamera& camera)
{
    Rectangle frustum = camera.getFrustum();
    Vector2 cameraPos = camera.getPosition();

    for (const auto& star : m_stars)
    {
        // 应用视差效果
        Vector2 renderPos = {
            star.position.x - cameraPos.x * star.parallaxFactor,
            star.position.y - cameraPos.y * star.parallaxFactor
        };

        // 检查星星是否在视锥体内
        if (renderPos.x >= frustum.x && renderPos.x <= frustum.x + frustum.width &&
            renderPos.y >= frustum.y && renderPos.y <= frustum.y + frustum.height)
        {
            RenderCommand cmd;
            cmd.type = RenderCommandType::Star;
            cmd.position = renderPos;
            cmd.size = { star.size, star.size };
            cmd.rotation = 0;
            cmd.color = star.color;
            cmd.layer = 0; // 星空在最底层

            commands.push_back(cmd);
        }
    }
}