#include "SDL.h"
#include <iostream>

#include "Vec2f.h"

using namespace gg::math; // from Vec2f.h

#pragma region DONT_EDIT

// renderer
SDL_Renderer* renderer = NULL;

// timers
static float game_time = 0.0f;
static float FPS = 60.0f;

// ID
static uint8_t COLOR_ID = 0;
static uint8_t CURRENT_COLOR = 0;

static int WIDTH = 800;
static int HEIGHT = 800;
static Vec2f origin;

struct Color
{
	uint8_t r, g, b, a;
	uint8_t ID;

	Color(void)
		: r(0), g(0), b(0), a(255), ID(++COLOR_ID)
	{ }

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: r(r), g(g), b(b), a(a), ID(++COLOR_ID)
	{ }
};
// These colors should only be the ones used (because of COLOR_ID hack)
static const Color White	=	Color(	255,	255,	255,	255);
static const Color Black	=	Color(	0,		0,		0,		255);
static const Color Red		=	Color(	255,	0,		0,		255);
static const Color Green	=	Color(	0,		255,	0,		255);
static const Color Blue		=	Color(	0,		0,		255,	255);

// functions
void onRender(float dt);
void drawLine(const Vec2f& from, const Vec2f& to, const Color& color = White);
void init(void);
void drawPoint(const Vec2f& position, const Color& color = White);
void drawRect(const Vec2f& position, const Vec2f& extents, const Color& color = White);

#pragma endregion DONT_EDIT

void init(void)
{
	WIDTH = 800;
	HEIGHT = 800;
	origin = Vec2f(0.5f * WIDTH, 0.5f * HEIGHT);
}

void onRender(float dt)
{
	// draw
	drawRect(origin, { 150, 150 });
	drawRect(origin + Vec2f(30, 30), { 20, 20 });
	drawRect(origin + Vec2f(-30, 30), { 20, 20 });
	drawLine(origin + Vec2f(-30, -30), origin + Vec2f(0, -20));
	drawLine(origin + Vec2f(30, -30), origin + Vec2f(0, -20));
}

#pragma region DONT_EDIT
int main(int argc, char *argv[])
{
	init();

	float _timer = 0.0f;
	float _prevTime = 0.0f;

	float _timestep = 1/FPS;


	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;

		if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;

			while (!done) {
				// update input
				SDL_Event event;
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
				}

				// clear frame
				CURRENT_COLOR = 0;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				// ++++++++++++++++ TIMER
				float _currTime = SDL_GetTicks() * 0.001f;
				float _delta = _currTime - _prevTime;
				_prevTime = _currTime;

				_timer += _delta;

				bool _willUpdate = _timer >= _timestep;
				if (_willUpdate)
				{
					// update delta time
					float _rem = std::fmod(_timer, _timestep);

					float _delta = _timer - _rem;
					game_time += _delta;
					
					onRender(_delta);

					SDL_RenderPresent(renderer);

					_timer = _rem;
				}
				// ---------------- TIMER
			}
		}

		if (renderer)
		{
			SDL_DestroyRenderer(renderer);
		}
		if (window)
		{
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}

void drawLine(const Vec2f& from, const Vec2f& to, const Color& color)
{
	if (CURRENT_COLOR != color.ID)
	{
		CURRENT_COLOR = color.ID;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawLineF(renderer, from.x, HEIGHT - from.y, to.x, HEIGHT - to.y);
}

void drawPoint(const Vec2f& position, const Color& color)
{
	if (CURRENT_COLOR != color.ID)
	{
		CURRENT_COLOR = color.ID;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawPointF(renderer, position.x, HEIGHT - position.y);
}

void drawRect(const Vec2f& position, const Vec2f& extents, const Color& color)
{
	if (CURRENT_COLOR != color.ID)
	{
		CURRENT_COLOR = color.ID;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawRectF(
		renderer,
		&SDL_FRect({
			position.x - 0.5f * extents.x,
			HEIGHT - position.y - 0.5f * extents.y,
			extents.x,
			extents.y,
		})
	);
}
#pragma endregion DONT_EDIT