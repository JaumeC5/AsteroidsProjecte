#pragma once

#include "Sprite.hh"
#include "Renderer.hh"


class Scene {
	Sprite m_b;
	int m_score;
	Sprite m_points;


public:
	Scene();
	void onEntry(char*);
	void onExit();
	void Update();
	void Draw();

};


Scene::Scene() {

}

void Scene::onEntry(char* dir) {
	m_b.setTexture(R.getRender(), dir); // direcció de la imatge de background
	m_b.setRect(0, 0, WIDTH, HEIGHT);
}

void Scene::Update() {

}

void Scene::Draw() {
	SDL_RenderCopy(R.getRender(), m_b.getTexture(), nullptr, &m_b.getRect());
}


