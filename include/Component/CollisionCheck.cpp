#include "CollisionCheck.h"

int CollisionCheck::CCW(const FVector2D& p0, const FVector2D& p1, const FVector2D& p2)
{
    float a = (p0.y - p1.y) / (p0.x - p1.x);
    float b = p0.y - a * p0.x;

    if (p2.y > (a * p2.x) + b)
        return 1;
    else if (p2.y < (a * p2.x + b))
        return -1;
    else
        return 0;
}
