#ifndef		WINDOW_H
#define		WINDOW_H
#pragma once

#include "Vec2f.h"
#include "Color.h"

namespace gg { namespace math { struct Vec2f; } }
using namespace gg::math;

struct SDL_Renderer;
struct SDL_Window;

class Window
{
public:
	void clear(const Color& bg = Color::Black);
	void submit(void);
	void destroy(void);

	void drawLine(const Vec2f& from, const Vec2f& to, const Color& color = Color::White);
	void drawPoint(const Vec2f& position, const Color& color = Color::White);
	void drawRect(const Vec2f& position, const Vec2f& extents, const Color& color = Color::White);

public:
	Window(int width, int height);

	uint8_t CURRENT_COLOR = 0;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
	int width, height;

private:
	Vec2f center;
};

#endif