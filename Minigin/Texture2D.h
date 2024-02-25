#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include <string>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final : public BaseComponent
	{
	public:
		Texture2D(GameObject* gameObject, const std::string& fileName);

		virtual ~Texture2D();
		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&&) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

		/*SDL_Texture* GetSDLTexture() const;
		glm::ivec2 GetSize() const;*/

		
	private:
		SDL_Texture* m_Texture;
	};
}
