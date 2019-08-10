#include "..\include\QuadTree.h"
#include "Vec2f.h"

#include <algorithm>
#include "Window.h"

QuadTree::QuadTree(const AABB& boundary)
	: boundary(boundary)
{ }
bool QuadTree::insert(const Vec2f& location)
{
	if (!boundary.containsPoint(location))
	{
		return false;
	}

	if (points.size() < QT_NODE_CAPACITY && nw == nullptr)
	{
		points.push_back(location);
		return true;
	}

	if (nw == nullptr)
	{
		subdivide();
	}

	if (nw->insert(location)) return true;
	if (ne->insert(location)) return true;
	if (sw->insert(location)) return true;
	if (se->insert(location)) return true;
	return false;
}

void QuadTree::subdivide(void)
{
	Vec2f _center = boundary.center;
	Vec2f _halfExtent = boundary.extent * 0.5f;

	nw = new QuadTree({ {_center.x - _halfExtent.x, _center.y + _halfExtent.y}, _halfExtent });
	ne = new QuadTree({ {_center.x + _halfExtent.x, _center.y + _halfExtent.y}, _halfExtent });
	sw = new QuadTree({ {_center.x - _halfExtent.x, _center.y - _halfExtent.y}, _halfExtent });
	se = new QuadTree({ {_center.x + _halfExtent.x, _center.y - _halfExtent.y}, _halfExtent });

	for (std::vector<Vec2f>::iterator it = points.begin(); it != points.end(); ++it)
	{
		if (nw->insert(*it)) { }
		else if (ne->insert(*it)) { }
		else if (sw->insert(*it)) { }
		else if (se->insert(*it)) { }
	}
	points.clear();
}

const std::vector<Vec2f> QuadTree::queryRange(const AABB& range)
{
	std::vector<Vec2f> _pointsInRange;

	if (!boundary.intersects(range))
	{
		return _pointsInRange;
	}

	for (std::vector<Vec2f>::iterator it = points.begin(); it != points.end(); ++it)
	{
		if (range.containsPoint((*it)))
		{
			_pointsInRange.push_back(*it);
		}
	}

	if (nw == nullptr)
	{
		return _pointsInRange;
	}
	
	std::vector<Vec2f> _nw = nw->queryRange(range);
	_pointsInRange.insert(_pointsInRange.end(), _nw.begin(), _nw.end());

	std::vector<Vec2f> _ne = ne->queryRange(range);
	_pointsInRange.insert(_pointsInRange.end(), _ne.begin(), _ne.end());

	std::vector<Vec2f> _sw = sw->queryRange(range);
	_pointsInRange.insert(_pointsInRange.end(), _sw.begin(), _sw.end());

	std::vector<Vec2f> _se = se->queryRange(range);
	_pointsInRange.insert(_pointsInRange.end(), _se.begin(), _se.end());

	return _pointsInRange;
}

void QuadTree::draw(Window* window)
{
	window->drawRect(boundary.center, boundary.extent);

	for (std::vector<Vec2f>::iterator it = points.begin(); it != points.end(); ++it)
	{
		window->drawPoint(*it);
	}

	if (nw == nullptr) { return; }

	nw->draw(window);
	ne->draw(window);
	sw->draw(window);
	se->draw(window);
}
