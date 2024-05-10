#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string name)
: m_ObjectAreDirty(false)
, m_name(std::move(name))
{}



Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetScene(this);
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(GameObject* object)
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

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
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

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		//collects all the images that need to be renderd.
		object->Render();
	}

	//todo: voeg hier een call naar de render singleton dat de buffer rendert.

}

void dae::Scene::HandleObjectRemoval()
{
	//this loop can be used if you want to set a dirty flag patern to say hey and object is removed. if you had a pointer to an object make shure it still is in the scene
	/*for (const auto& component : m_Components) {
		component->SetComponentDirty();
	}*/

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
