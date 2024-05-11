#include "SceneManager.h"

#include <iostream>

#include "Renderer.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_MapOfScenes[m_ActiveScene]->Update();
}

void dae::SceneManager::FixedUpdate()
{
	m_MapOfScenes[m_ActiveScene]->FixedUpdate();
}

void dae::SceneManager::Render()
{
	m_MapOfScenes[m_ActiveScene]->Render();
}

void dae::SceneManager::OpenSceneByName(std::string name)
{
	if(m_MapOfScenes.contains(name))
	{
		m_ActiveScene = name;
		return;
	}

	std::cout << "error : no scene by the name of " << name << " was found.\n";
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));

	m_MapOfScenes[name] = scene;

	if(m_ActiveScene.empty())
	{
		m_ActiveScene = name;
	}

	return *scene;
}
