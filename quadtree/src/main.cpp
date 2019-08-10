#include <iostream>
#include "SDL.h"

#include "Window.h"
#include "Vec2f.h"
#include "QuadTree.h"

using namespace gg::math; // from Vec2f.h

#pragma region VARIABLES
// timers
static float game_time = 0.0f;
static float FPS = 60.0f;
Window* window = new Window(800, 800);
QuadTree* qt;
#pragma endregion VARIABLES

#pragma region FUNCTION_DECLARATIONS
void init(void);
void onRender(float dt);
void onExit(void);
float getRandFloat(float min, float max);
#pragma endregion FUNCTION_DECLARATIONS

void init(void)
{
	const Vec2f& _origin = window->origin;
	float _w = (float)window->width;
	float _h = (float)window->height;

	qt = new QuadTree({ _origin, { 0.5f * _w, 0.5f * _h} });
	for (int i = -1; ++i < 100; )
	{
		float _x = getRandFloat(0, _w);
		float _y = getRandFloat(0, _h);
		qt->insert({ _x, _y });
	}
}

void onRender(float dt)
{
	//const Vec2f& _origin = window->origin;

	// draw sad face
	//window->drawRect(_origin, { 75, 75 });
	//window->drawRect(_origin + Vec2f(30, 30), { 20, 20 });
	//window->drawRect(_origin + Vec2f(-30, 30), { 20, 20 });
	//window->drawLine(_origin + Vec2f(-30, -30), _origin + Vec2f(0, -20));
	//window->drawLine(_origin + Vec2f(30, -30), _origin + Vec2f(0, -20));

	//std::cout << 1 / dt << std::endl;
	qt->draw(window);
}

void onExit(void)
{
	qt->freeRecursive();
	delete qt;
}

int main(int argc, char *argv[])
{
	init();

	float _timer = 0.0f;
	float _prevTime = 0.0f;

	float _timestep = 1/FPS;


	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		if (SDL_CreateWindowAndRenderer(window->width, window->height, 0, &window->window, &window->renderer) == 0)
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
				window->clear();

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

					window->submit();

					_timer = _rem;
				}
				// ---------------- TIMER
			}
		}

		onExit();
		window->destroy();
	}

	SDL_Quit();
	return 0;
}

float getRandFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
