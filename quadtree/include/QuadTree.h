#ifndef		QUADTREE_H
#define		QUADTREE_H
#pragma once

#include <vector>
#include "AABB.h"
#include "Vec2f.h"

namespace gg { namespace math { struct Vec2f; } }
using namespace gg::math;

class Window;
struct QuadTree
{
public:
	QuadTree(const AABB& boundary);
	~QuadTree(void);

	const AABB& getBoundary(void) const { return boundary; }
	const std::vector<Vec2f>& getPoints(void) const { return points; }

	bool insert(const Vec2f& location);
	void subdivide(void);
	const std::vector<Vec2f> queryRange(const AABB& range);

	void draw(Window* window);

	void freeRecursive(void);

private:
	static const int QT_NODE_CAPACITY = 4;

	AABB boundary;

	std::vector<Vec2f> points;

	// Children
	QuadTree* nw = nullptr;
	QuadTree* ne = nullptr;
	QuadTree* sw = nullptr;
	QuadTree* se = nullptr;
};
#endif