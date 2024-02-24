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
#include "Scene.h"

#include "GameObject.h"

//this function creates a scene and adds the components to it.
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>(std::make_shared<dae::Transform>());

	go->AddComponent(std::make_shared<dae::Texture2D>("background.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>(std::make_shared<dae::Transform>(216.f, 180.f, 0.f));
	go->AddComponent(std::make_shared<dae::Texture2D>("logo.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>(std::make_shared<dae::Transform>(80.f, 20.f, 0.f));
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_shared<dae::TextComponent>("Programming 4 Assignment", font));
	scene.Add(go);
}

int main(int, char*[]) {
	//creates the minigin
	dae::Minigin engine("../Data/");
	
	//adds a reference to the function load that can then be executed in the minigin run function.
	engine.Run(load);
    return 0;
}