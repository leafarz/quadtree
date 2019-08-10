#include "Window.h"

#include "SDL.h"

Window::Window(int width, int height)
	: width(width), height(height), origin({(float)width * 0.5f, (float)height * 0.5f})
{

}

void Window::clear(const Color& bg)
{
	SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	CURRENT_COLOR = 0;
}

void Window::submit(void)
{
	SDL_RenderPresent(renderer);
}

void Window::destroy(void)
{
	if (renderer) { SDL_DestroyRenderer(renderer); }
	if (window) { SDL_DestroyWindow(window); }
}

void Window::drawLine(const Vec2f& from, const Vec2f& to, const Color& color)
{
	if (CURRENT_COLOR != color.ID)
	{
		CURRENT_COLOR = color.ID;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawLineF(renderer, from.x, height - from.y, to.x, height - to.y);
}

void Window::drawPoint(const Vec2f& position, const Color& color)
{
	if (CURRENT_COLOR != color.ID)
	{
		CURRENT_COLOR = color.ID;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawPointF(renderer, position.x, height - position.y);
}

void Window::drawRect(const Vec2f& position, const Vec2f& extents, const Color& color)
{
	if (CURRENT_COLOR != color.ID)
	{
		CURRENT_COLOR = color.ID;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawRectF(
		renderer,
		&SDL_FRect({
			position.x - extents.x,
			height - position.y - extents.y,
			extents.x + extents.x,
			extents.y + extents.y,
			})
		);
}