#include "AABB.h"

AABB::AABB(void)
{ }

AABB::AABB(const Vec2f& center, const Vec2f& extent)
	: center(center), extent(extent)
{ }

bool AABB::containsPoint(const Vec2f& position) const
{
	Vec2f _min = center - extent;
	Vec2f _max = center + extent;

	return	_min.x <= position.x && position.x <= _max.x &&
			_min.y <= position.y && position.y <= _max.y;
}

bool AABB::intersects(const AABB& other) const
{
	Vec2f _min = center - extent;
	Vec2f _max = center + extent;

	Vec2f _otherMin = other.center - other.extent;
	Vec2f _otherMax = other.center + other.extent;

	return	_min.x <= _otherMax.x && _max.x >= _otherMin.x &&
			_min.y <= _otherMax.y && _max.y >= _otherMin.y;
}

