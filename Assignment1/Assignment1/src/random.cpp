// math.cpp

#include "coconut.hpp"
#include "raylib.h"

namespace coconut
{
   namespace Random
   {
      float range01()
      {
         return GetRandomValue(0, 65536) / 65536.0f;
      }

      float range(float min, float max)
      {
         return min + (max - min) * range01();
      }

      int32 range_int(int32 min, int32 max)
      {
         return GetRandomValue(min, max);
      }
   } // !Random
} // !coconut
