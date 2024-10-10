#include "Vector2.h"
#include <math.h>

float VSize(VECTOR2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

VECTOR2 VSub(VECTOR2 v1, VECTOR2 v2)
{
    VECTOR2 r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    return r;
}

VECTOR2 VAdd(VECTOR2 v1, VECTOR2 v2)
{
    VECTOR2 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

VECTOR2 operator +(VECTOR2 v1, VECTOR2 v2)
{
    VECTOR2 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

VECTOR2 VScale(VECTOR2 v, float s)
{
    VECTOR2 r;
    r.x = v.x * s;
    r.y = v.y * s;
    return r;
}

VECTOR2 VNorm(VECTOR2 v)
{
    float len = VSize(v);
    return VScale(v, 1.0f / len);
}

bool CircleHit(VECTOR2 obj1, VECTOR2 obj2, float r)
{
    VECTOR2 d = VSub(obj1, obj2); // ç∑
    if (VSize(d) < r) { // obj1Ç∆obj2ÇÃãóó£Ç™îºåaÇÊÇËè¨Ç≥Ç¢
        return true; // ìñÇΩÇ¡ÇƒÇ¢ÇÈÇÃÇ≈ÅAtrue
    }
    return false; // ìñÇΩÇ¡ÇƒÇ»Ç¢
}
