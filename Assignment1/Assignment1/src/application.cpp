// application.cpp

#include "coconut.hpp"

namespace coconut
{
   bool Application::initialize(int32 width, int32 height)
   {
      m_width = width;
      m_height = height;

      m_camera.set_position(Vector2{ m_width * 0.5f, m_height * 0.5f });
      m_camera.set_extent(Vector2{ 128, 72 });
      m_starfield.randomize(m_width, m_height);

      return true;
   }

   void Application::shutdown()
   {
   }

   bool Application::update()
   {
      // note: early exit
      if (IsKeyReleased(KEY_ESCAPE)) {
         m_running = false;
      }

      // note: simple camera controller
      m_camera.set_position( GetMousePosition() );

      // note: simple starfield controller
      if (IsKeyPressed(KEY_SPACE)) {
         m_starfield.toggle_culling();
      }
      if (IsKeyPressed(KEY_R)) {
         m_starfield.randomize(m_width, m_height);
      }

      // note: update state
      m_camera.update();
      m_starfield.update(m_camera);

      return m_running;
   }

   void Application::render()
   {
      m_starfield.render();
      m_camera.render();

      // note: potentially add toggle for debug drawing (global or...)
      m_starfield.debug_render();
   }
} // !coconut
