#include "Scene.h"

#include "Application.h"
#include "Window.h"

#include "QuadTree.h"

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
	delete m_QuadTree;
	delete this;
}

float Scene::getRandFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

void Scene::onStart(void)
{
	Application* _app = Application::getInstance();
	Window* _window = _app->getWindow();

	float _w = (float)_window->getWidth() * 0.5f;
	float _h = (float)_window->getHeight() * 0.5f;

	m_QuadTree = new QuadTree({ {0, 0}, { _w, _h} });
	for (int i = -1; ++i < 100; )
	{
		float _x = getRandFloat(-_w, _w);
		float _y = getRandFloat(-_h, _h);
		m_QuadTree->insert({ _x, _y });
	}
}

void Scene::onRender(float dt)
{
	Application* _app = Application::getInstance();
	Window* _window = _app->getWindow();

	// draw sad face
	//window->drawRect({ 0,0 }, { 75, 75 });
	//window->drawRect(Vec2f(30, 30), { 20, 20 });
	//window->drawRect(Vec2f(-30, 30), { 20, 20 });
	//window->drawLine(Vec2f(-30, -30), Vec2f(0, -20));
	//window->drawLine(Vec2f(30, -30), Vec2f(0, -20));

	//std::cout << 1 / dt << std::endl;
	m_QuadTree->draw(_window);
}

void Scene::onEnd(void)
{
}
