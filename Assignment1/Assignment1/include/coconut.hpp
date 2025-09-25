// coconut.hpp

#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <raylib.h>

namespace coconut
{
   using uint64 = unsigned long long;
   using  int64 =   signed long long;
   using uint32 = unsigned int;
   using  int32 =   signed int;
   using uint16 = unsigned short;
   using  int16 =   signed short;
   using  uint8 = unsigned char;
   using   int8 =   signed char;

   namespace Random
   {
      float range01();
      float range(float min, float max);
      int32 range_int(int32 min, int32 max);
   } // !Random

   struct Camera {
      Camera() = default;

      void set_position(Vector2 position);
      void set_extent(Vector2 extent);
      void update();
      void render();

      Vector2   m_position = {};
      Vector2   m_extent = {};
      Rectangle m_frustum = {};
   };

   struct Star {
      Star() = default;

      void initialize(Rectangle area, Color color);
      void set_visible(bool state);
      void render();

      bool      m_visible = true;
      Rectangle m_area = {};
      Color     m_color = {};
   };

   struct Starfield {
      static constexpr int32 STAR_COUNT = 8*1024;

      Starfield() = default;

      void randomize(int32 width, int32 height);
      void toggle_culling();
      void update(const Camera &camera);
      void render();
      void debug_render();

      bool  m_culling = true;
      int32 m_visible_stars = 0;
      Star  m_stars[STAR_COUNT] = {};
   };

   struct Application {
      Application() = default;

      bool initialize(int32 width, int32 height);
      void shutdown();
      bool update();
      void render();

      bool      m_running = true;
      int32     m_width = 0;
      int32     m_height = 0;
      Camera    m_camera;
      Starfield m_starfield;
   };
} // !coconut
