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
        // ���λ�� (����Ļ����չ����)
        star.position = {
            MathUtils::random(-(float)screenWidth, (float)screenWidth * 2),
            MathUtils::random(-(float)screenHeight, (float)screenHeight * 2)
        };

        // �����С����ɫ
        star.size = MathUtils::random(1.0f, 3.0f);

        unsigned char brightness = (unsigned char)MathUtils::random(100, 255);
        star.color = { brightness, brightness, brightness, 255 };

        // ����Ӳ����� (0.1-0.9)
        star.parallaxFactor = MathUtils::random(0.1f, 0.9f);
    }
}

void Starfield::addRenderCommands(std::vector<RenderCommand>& commands, const GameCamera& camera)
{
    Rectangle frustum = camera.getFrustum();
    Vector2 cameraPos = camera.getPosition();

    for (const auto& star : m_stars)
    {
        // Ӧ���Ӳ�Ч��
        Vector2 renderPos = {
            star.position.x - cameraPos.x * star.parallaxFactor,
            star.position.y - cameraPos.y * star.parallaxFactor
        };

        // ��������Ƿ�����׶����
        if (renderPos.x >= frustum.x && renderPos.x <= frustum.x + frustum.width &&
            renderPos.y >= frustum.y && renderPos.y <= frustum.y + frustum.height)
        {
            RenderCommand cmd;
            cmd.type = RenderCommandType::Star;
            cmd.position = renderPos;
            cmd.size = { star.size, star.size };
            cmd.rotation = 0;
            cmd.color = star.color;
            cmd.layer = 0; // �ǿ�����ײ�

            commands.push_back(cmd);
        }
    }
}