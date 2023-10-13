#include "Scene.h"

Scene::Scene()
{
	globalLight.position = { 0.0f, 100.0f, 0.0f };
	globalLight.color = { 1, 1, 1 };
	globalLight.intensity = 0.5f;
}

Scene::~Scene()
{
}

void Scene::AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	m_objectMap[name] = object;
}

void Scene::Update(double elapsedSeconds)
{
	for (const auto& element : m_objectMap) {
		const auto& object = element.second;
		object->Update(elapsedSeconds);
	}
}

