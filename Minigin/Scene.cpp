#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

#include "Renderer.h"


int dae::Scene::m_CurrentIndex = 0;

std::vector<std::shared_ptr<dae::GameObject>> dae::Scene::GetObjectsInScene() const
{
	return m_objects;
}

std::vector<std::shared_ptr<dae::GameObject>> dae::Scene::GetObjectsByName(std::string name) const
{
	std::vector<std::shared_ptr<GameObject>> results;

	for (auto gameObject : m_objects)
	{
		if(gameObject->GetObjectName() == name)
		{
			results.push_back(gameObject);
		}
	}

	return results;
}

std::shared_ptr<dae::GameObject> dae::Scene::GetObjectByName(std::string name) const
{
	std::vector<std::shared_ptr<GameObject>> results;

	for (auto gameObject : m_objects)
	{
		if (gameObject->GetObjectName() == name)
		{
			return gameObject;
		}
	}

	return nullptr;
}

dae::Scene::Scene(std::string name)
: m_ObjectAreDirty(false)
, m_Name(std::move(name))
{}


dae::Scene::~Scene() = default;

void dae::Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetScene(this);
	m_objects.emplace_back(std::move(object));
}

void dae::Scene::Remove(GameObject* object)
{
	if(object != nullptr)
	{
		object->SetParentGameObject(nullptr);

		for(int index = 0; index < static_cast<signed int>(object->GetChildCount()); ++index)
		{
			Remove(object->GetChildAt(index));
		}

		m_RemovalList.emplace_back(object);
		m_ObjectAreDirty = true;
	}
}

void dae::Scene::RemoveAll()
{
	m_objects.clear();
}

void dae::Scene::Update()
{
	for(const auto& object : m_objects)
	{
		object->Update();
	}

	if(m_ObjectAreDirty)
	{
		HandleObjectRemoval();
	}
}

void dae::Scene::FixedUpdate() const
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void dae::Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		//collects all the images that need to be renderd.
		object->Render();
	}

	//todo: voeg hier een call naar de render singleton dat de buffer rendert.
	Renderer::GetInstance().DisplayRenderMap();
}

void dae::Scene::HandleObjectRemoval()
{
	for (auto rawPtr : m_RemovalList) {
		std::erase_if(m_objects, [&](std::shared_ptr<GameObject>& ptr)
			{
				if (ptr.get() == rawPtr)
				{
					ptr.reset();
					return true;
				}
				return false;
			});
	}
	m_RemovalList.clear();

	m_ObjectAreDirty = false;
}
