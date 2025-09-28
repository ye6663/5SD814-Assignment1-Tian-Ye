// grid.cpp

#include "grid.hpp"
#include "math_utils.hpp"
#include <raylib.h>
#include <iostream>

void Grid::initialize(int width, int height, int cellWidth, int cellHeight)
{
    m_width = width;
    m_height = height;
    m_cellWidth = cellWidth;
    m_cellHeight = cellHeight;

    m_cells.resize(width * height);

    std::cout << "Grid initialized: " << width << "x" << height
        << " (" << width * height << " cells)" << std::endl;
}

void Grid::generateAsteroids(int count)
{
    for (int i = 0; i < count; i++)
    {
        Asteroid asteroid;

        // ���λ�������緶Χ��
        Vector2 position = {
            (float)MathUtils::random(0, m_width * m_cellWidth),
            (float)MathUtils::random(0, m_height * m_cellHeight)
        };

        // �����С (С���С���)
        float sizeType = (float)MathUtils::random(0, 3);
        Vector2 size;
        int layer;

        if (sizeType < 1.0f) {
            size = { 20, 20 };
            layer = 1; // ������
        }
        else if (sizeType < 2.0f) {
            size = { 40, 40 };
            layer = 2; // �м��
        }
        else {
            size = { 60, 60 };
            layer = 3; // ǰ����
        }

        // �����ת����ת����
        float rotation = (float)MathUtils::random(0, 360);
        float rotationSpeed = MathUtils::random(0.2f, 1.0f);
        if (MathUtils::random(0, 2) < 1.0f) {
            rotationSpeed = -rotationSpeed; // ���˳ʱ�����ʱ��
        }

        // �����ɫ (�Ҷ�)
        unsigned char gray = (unsigned char)MathUtils::random(150, 230);
        Color color = { gray, gray, gray, 255 };

        asteroid.initialize(position, size, rotation, rotationSpeed, color, layer);

        // ��ӵ���Ӧ������Ԫ
        int gridX, gridY;
        worldToGrid(position, gridX, gridY);

        if (gridX >= 0 && gridX < m_width && gridY >= 0 && gridY < m_height)
        {
            int index = gridY * m_width + gridX;
            m_cells[index].asteroids.push_back(asteroid);
        }
    }

    std::cout << "Generated " << count << " asteroids" << std::endl;
}

void Grid::updateAsteroids()
{
    for (auto& cell : m_cells)
    {
        for (auto& asteroid : cell.asteroids)
        {
            asteroid.update();
        }
    }
}

std::vector<Asteroid> Grid::getVisibleAsteroids(const Rectangle& frustum2) const
{
    std::vector<Asteroid> result;

    int startX = 0;
    int endX = 9;

    int startY = 0;
    int endY = 9;

    // �����ɼ�������Ԫ
    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            int index = y * m_width + x;
            const auto& cell = m_cells[index];

            for (const auto& asteroid : cell.asteroids)
            {
                Rectangle asteroidRect = {
                    asteroid.position.x - asteroid.size.x / 2,
                    asteroid.position.y - asteroid.size.y / 2,
                    asteroid.size.x,
                    asteroid.size.y
                };

                result.push_back(asteroid);
            }
        }
    }

    return result;
}

void Grid::renderDebug() const
{
     // ����С��ͼ
    int miniMapSize = 200;
    int miniMapX = m_width - miniMapSize - 10;
    int miniMapY = 10;

    // С��ͼ����
    DrawRectangle(miniMapX, miniMapY, miniMapSize, miniMapSize, Fade(BLACK, 0.5f));

    // �������ű���
    float scale = static_cast<float>(miniMapSize) / (m_width * m_cellWidth);

    // ��������
    for (int x = 0; x <= m_width; x++)
    {
        int lineX = miniMapX + (int)(x * m_cellWidth * scale);
        DrawLine(lineX, miniMapY, lineX, miniMapY + miniMapSize, DARKGRAY);
    }

    for (int y = 0; y <= m_height; y++)
    {
        int lineY = miniMapY + (int)(y * m_cellHeight * scale);
        DrawLine(miniMapX, lineY, miniMapX + miniMapSize, lineY, DARKGRAY);
    }
}

void Grid::worldToGrid(const Vector2& position, int& gridX, int& gridY) const
{
    gridX = static_cast<int>(position.x) / m_cellWidth;
    gridY = static_cast<int>(position.y) / m_cellHeight;
}

bool Grid::isCellVisible(int gridX, int gridY, const Rectangle& frustum) const
{
    Rectangle cellRect = {
        static_cast<float>(gridX * m_cellWidth),
        static_cast<float>(gridY * m_cellHeight),
        static_cast<float>(m_cellWidth),
        static_cast<float>(m_cellHeight)
    };

    return CheckCollisionRecs(cellRect, frustum);
}