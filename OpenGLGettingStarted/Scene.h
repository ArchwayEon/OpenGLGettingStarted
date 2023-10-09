#pragma once
#include <memory>
#include <map>
#include <string>
#include "GraphicsObject.h"

class Scene
{
protected:
	std::map<std::string, std::shared_ptr<GraphicsObject>> m_objects;
public:
	Scene();
	~Scene();
	void AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object);
	void Render();
};

