#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "BaseComponent.h"



dae::GameObject::GameObject(std::shared_ptr<Transform> transform):
	m_Transform(transform)
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto &component : m_Components) {
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	const auto& pos = m_Transform->GetPosition();
	for (auto& component : m_Components) {
		component->Render(pos.x, pos.y);
	}
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

//void dae::GameObject::SetPosition(float x, float y)
//{
//	m_transform.SetPosition(x, y, 0.0f);
//}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_Components.emplace_back(std::move(component));
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
	m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
}
