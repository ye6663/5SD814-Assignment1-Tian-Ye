// grid.hpp

#pragma once
#include "asteroid.hpp"
#include "game_camera.hpp"
#include <vector>
#include <raylib.h>

struct GridCell
{
    std::vector<Asteroid> asteroids;
};

class Grid
{
public:
    void initialize(int width, int height, int cellWidth, int cellHeight);
    void generateAsteroids(int count);
    void updateAsteroids();
    
    std::vector<Asteroid> getVisibleAsteroids(const Rectangle& frustum) const;
    
    void renderDebug(const GameCamera& camera) const;
    
private:
    int m_width = 0;
    int m_height = 0;
    int m_cellWidth = 0;
    int m_cellHeight = 0;
    
    std::vector<GridCell> m_cells;
    
    // 将世界坐标转换为网格坐标
    void worldToGrid(const Vector2& position, int& gridX, int& gridY) const;
    
    // 检查网格单元是否在视锥体内
    bool isCellVisible(int gridX, int gridY, const Rectangle& frustum) const;
};