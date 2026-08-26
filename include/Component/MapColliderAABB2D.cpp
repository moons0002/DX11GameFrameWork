#include "MapColliderAABB2D.h"

void MapColliderAABB2D::UpdateTransform()
{
	mMin = mCenter - (mSize/2);
	mMax = mCenter + (mSize/2);
}