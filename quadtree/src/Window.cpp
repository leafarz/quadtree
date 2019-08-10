#include "Window.h"

#include "SDL.h"

Window::Window(int width, int height)
	: width(width), height(height), center({(float)width * 0.5f, (float)height * 0.5f})
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
	if (CURRENT_COLOR != color.getID())
	{
		CURRENT_COLOR = color.getID();
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawLineF(renderer, center.x + from.x, height - (center.x + from.y), center.x + to.x, height - (center.y + to.y));
}

void Window::drawPoint(const Vec2f& position, const Color& color)
{
	if (CURRENT_COLOR != color.getID())
	{
		CURRENT_COLOR = color.getID();
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawPointF(renderer, position.x + center.x, height - (center.y + position.y));
}

void Window::drawRect(const Vec2f& position, const Vec2f& extents, const Color& color)
{
	if (CURRENT_COLOR != color.getID())
	{
		CURRENT_COLOR = color.getID();
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawRectF(
		renderer,
		&SDL_FRect({
			center.x + position.x - extents.x,
			height - (center.y + position.y + extents.y),
			extents.x + extents.x,
			extents.y + extents.y,
			})
		);
}