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
	Window(int width, int height);

	SDL_Renderer** getRenderer(void) { return &renderer; }
	SDL_Window** getWindow(void) { return &window; }
	int getWidth(void) const { return width; }
	int getHeight(void) const { return height; }

	void clear(const Color& bg = Color::Black);
	void submit(void);
	void destroy(void);

	void drawLine(const Vec2f& from, const Vec2f& to, const Color& color = Color::White);
	void drawPoint(const Vec2f& position, const Color& color = Color::White);
	void drawRect(const Vec2f& position, const Vec2f& extents, const Color& color = Color::White);

private:
	uint8_t CURRENT_COLOR = 0;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
	int width, height;
	Vec2f center;
};

#endif