#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::GameObject(const Transform& transform)
	: m_PositionIsDirty(false)
	, m_LocalTransform(transform)
	, m_WorldTransform(transform)
	, m_Parent(nullptr)
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update() const
{
	for (auto &component : m_Components) {
		component->Update();
	}
}

void dae::GameObject::FixedUpdate(float fixedTimeStep) const
{
	for (auto& component : m_Components) {
		component->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::Render() const
{
	for (auto& component : m_Components) {
		component->Render(m_WorldTransform.position.x, m_WorldTransform.position.y);
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	m_Components.emplace_back(std::move(component));
}

void dae::GameObject::SetParentGameObject(GameObject* parentObject, const bool keepWorldPosition)
{
	if(IsChild(parentObject) ||parentObject == this || m_Parent == parentObject )
	{
		return;
	}

	if(parentObject == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if(keepWorldPosition)
		{
			//if you want the world space - world space new parent is vector. parent is 0 point.
			SetLocalPosition(GetWorldPosition() - parentObject->GetWorldPosition());
		}
		SetPositionDirty();
	}

	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parentObject;
	if (m_Parent) m_Parent->AddChild(this);
}

void dae::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_LocalTransform.SetPosition(position);
	SetPositionDirty();
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if(m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldTransform.position;
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (const auto child : m_Children)
	{
		child->SetPositionDirty();
		child->UpdateWorldPosition();
	}
}


#pragma region private functions
void dae::GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::ranges::find(m_Children, child));
}

bool dae::GameObject::IsChild(GameObject* gameObject)
{
	return (std::ranges::find(m_Children, gameObject) != m_Children.end());
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_Parent == nullptr)
		{
			m_WorldTransform.SetPosition(m_LocalTransform.position);
		}
		else
		{
			m_WorldTransform.SetPosition(m_Parent->GetWorldPosition() + m_LocalTransform.position);
		}
	}
	m_PositionIsDirty = false;
}
#pragma endregion 


