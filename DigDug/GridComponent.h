#pragma once
#include "BaseComponent.h"

class GridComponent final : public dae::BaseComponent
{
public:
	explicit GridComponent(dae::GameObject* gameObject);

	~GridComponent() override = default;
	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	std::vector<glm::ivec2> m_GridPositions;

};
