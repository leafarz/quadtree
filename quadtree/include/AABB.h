#ifndef		AABB_H
#define		AABB_H
#pragma once

#include "Vec2f.h"

namespace gg { namespace math { struct Vec2f; } }
using namespace gg::math;

struct AABB
{
public:
	AABB(void);
	AABB(const Vec2f& center, const Vec2f& extent);

	bool containsPoint(const Vec2f& position) const;
	bool intersects(const AABB& other) const;

	Vec2f center;
	Vec2f extent;
};

#endif