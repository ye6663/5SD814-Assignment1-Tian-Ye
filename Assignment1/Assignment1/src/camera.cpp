// camera.cpp

#include "coconut.hpp"
#include "raymath.h"

namespace coconut
{
   void Camera::set_position(Vector2 position)
   {
      m_position = position;
   }

   void Camera::set_extent(Vector2 extent)
   {
      m_extent = extent;
   }

   void Camera::update()
   {
      m_frustum.x = m_position.x - m_extent.x;
      m_frustum.y = m_position.y - m_extent.y;
      m_frustum.width = m_extent.x * 2.0f;
      m_frustum.height = m_extent.y * 2.0f;
   }

   void Camera::render()
   {
      DrawRectangleLinesEx(m_frustum, 1.0f, WHITE);
   }
} // !coconut
