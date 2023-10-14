#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "GraphicsObject.h"
#include "Camera.h"
#include "GraphicsStructures.h"

class Scene
{
protected:
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> m_objectMap;
public:
	std::shared_ptr<Camera> camera;
	Light globalLight;

public:
	Scene();
	~Scene();
	void AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object);
	void Update(double elapsedSeconds);
	const std::unordered_map<std::string, std::shared_ptr<GraphicsObject>>& GetObjectMap() 
	{
		return m_objectMap;
	}
};

