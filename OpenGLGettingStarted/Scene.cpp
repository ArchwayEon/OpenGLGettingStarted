#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	m_objectMap[name] = object;
}

//void Scene::Render()
//{
//	for (const auto& element : m_objectMap) {
//		const auto& object = element.second;
//		object->Render(camera);
//	}
//}
