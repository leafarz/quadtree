#ifndef		SCENE_H
#define		SCENE_H
#pragma once

struct QuadTree;

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void onStart(void);
	void onRender(float dt);
	void onEnd(void);

private:
	float getRandFloat(float min, float max);
private:
	QuadTree* m_QuadTree;
};
#endif