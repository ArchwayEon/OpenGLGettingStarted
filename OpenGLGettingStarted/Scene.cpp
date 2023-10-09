#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	m_objects[name] = object;
}

void Scene::Render()
{
	for (const auto& object : m_objects) {
		object.second->Render();
	}
}
