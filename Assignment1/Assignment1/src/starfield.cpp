// starfield.cpp

#include "coconut.hpp"

namespace coconut
{
   void Star::initialize(Rectangle area, Color color)
   {
      m_area = area;
      m_color = color;
   }

   void Star::set_visible(bool state)
   {
      m_visible = state;
   }

   void Star::render()
   {
      if (!m_visible) {
         return;
      }

      DrawRectangleRec(m_area, m_color);
   }

   void Starfield::randomize(int32 width, int32 height)
   {
      for (auto &star : m_stars) {
         const float size = Random::range_int(2, 4) * 1.0f;
         const Rectangle area = {
            .x = Random::range(size, width - size * 2.0f),
            .y = Random::range(size, height - size * 2.0f),
            .width = size,
            .height = size
         };
         const Color color = ColorAlpha(WHITE, 1.0f - Random::range01() * 0.8f);

         star.initialize(area, color);
      }
   }

   void Starfield::toggle_culling()
   {
      m_culling = !m_culling;
   }

   void Starfield::update(const Camera &camera)
   {
      m_visible_stars = 0;
      for (auto &star : m_stars) {
         bool overlap = CheckCollisionRecs(star.m_area, camera.m_frustum);
         bool visible = overlap || !m_culling;
         star.set_visible(visible);
         m_visible_stars += (visible);
      }
   }

   void Starfield::render()
   {
      for (auto &star : m_stars) {
         star.render();
      }
   }

   void Starfield::debug_render()
   {
      constexpr int FONT_SIZE = 20;
      DrawText(TextFormat("Visible: %d/%d", m_visible_stars, STAR_COUNT), 2, 2, FONT_SIZE, MAGENTA);
   }
} // !coconut
