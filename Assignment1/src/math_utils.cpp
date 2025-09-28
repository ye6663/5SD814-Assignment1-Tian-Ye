// math_utils.cpp

#include "math_utils.hpp"
#include <raylib.h>
#include <random>
#include <algorithm>

namespace MathUtils
{
    float random(float min, float max)
    {
        return min + static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f * (max - min);
    }

    int random(int min, int max)
    {
        return GetRandomValue(min, max);
    }

    // 线性插值
    float lerp(float start, float end, float t)
    {
        // 确保t在[0,1]范围内
        t = clamp(t, 0.0f, 1.0f);
        return start + (end - start) * t;
    }

    // 二维向量线性插值
    struct Vector2 lerp(const struct Vector2& start, const struct Vector2& end, float t)
    {
        t = clamp(t, 0.0f, 1.0f);
        return {
            start.x + (end.x - start.x) * t,
            start.y + (end.y - start.y) * t
        };
    }

    // 缓入缓出函数 (使用三次函数)
    float easeInOut(float t)
    {
        t = clamp(t, 0.0f, 1.0f);
        return t < 0.5f ? 4.0f * t * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
    }

    // 缓入函数
    float easeIn(float t)
    {
        t = clamp(t, 0.0f, 1.0f);
        return t * t;
    }

    // 缓出函数
    float easeOut(float t)
    {
        t = clamp(t, 0.0f, 1.0f);
        return 1.0f - (1.0f - t) * (1.0f - t);
    }

    // 钳制函数
    float clamp(float value, float min, float max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
}