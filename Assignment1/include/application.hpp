#pragma once
#include "game_camera.hpp"
#include "player.hpp"
#include "grid.hpp"
#include "starfield.hpp"
#include "render_command.hpp"
#include <vector>

class Application
{
public:
    bool initialize(int width, int height);
    void shutdown();
    void update();
    void render();
    
private:
    int m_width = 1920;
    int m_height = 1082;
    
    GameCamera m_camera;
    Player m_player;
    Grid m_grid;
    Starfield m_starfield;
    
    // 渲染命令队列
    std::vector<RenderCommand> m_renderCommands;
    
    // 调试信息
    bool m_showDebug = true;
    int m_totalAsteroids = 0;
    int m_visibleAsteroids = 0;
    
    void processInput();
    void updateCamera();
    void collectRenderCommands();
    void renderDebugInfo();
};