#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "Scene.h"

#include "GameObject.h"
#include "RenderComponent.h"

#include "Transform.h"

//this function creates a scene and adds the components to it.
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	dae::Transform position{};
	position.SetPosition(0.f, 0.f, 0.f);
	auto go = std::make_shared<dae::GameObject>(position);

	go->AddComponent(std::make_shared<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("background.tga")));
	scene.Add(go);


	position.SetPosition(216.f, 180.f, 0.f);
	go = std::make_shared<dae::GameObject>(position);
	go->AddComponent(std::make_shared<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("logo.tga")));
	scene.Add(go);

	position.SetPosition(80.f, 20.f, 0.f);
	go = std::make_shared<dae::GameObject>(position);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_shared<dae::RenderComponent>(go.get()));
	go->AddComponent(std::make_shared<dae::TextComponent>(go.get(), font, "Programming 4 Assignment" ));

	//go->RemoveComponent(go->GetComponent<dae::TextComponent>());
	//if(go->HasComponent<dae::TextComponent>())
	//{
	//	std::cout << "yes it works";
	//}
	
	scene.Add(go);

	position.SetPosition();
	go = std::make_shared<dae::GameObject>(position);
	go->AddComponent(std::make_shared<dae::RenderComponent>(go.get()));
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_shared<dae::TextComponent>(go.get(), font));
	go->AddComponent(std::make_shared<dae::FpsComponent>(go.get()));
	scene.Add(go);
}

int main(int, char*[]) {
	//creates the minigin
	dae::Minigin engine("../Data/");
	
	//adds a reference to the function load that can then be executed in the minigin run function.
	engine.Run(load);
    return 0;
}