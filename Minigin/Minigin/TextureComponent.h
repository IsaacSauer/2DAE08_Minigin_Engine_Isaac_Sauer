#pragma once
#include "MonoBehavior.h"
#include "Texture2D.h"

namespace dae
{
	class TextureComponent final : public MonoBehavior
	{
	public:
	
		virtual void FixedUpdate() override;
		virtual void Update() override;
	public:
		TextureComponent() = default;
		TextureComponent(std::shared_ptr<Texture2D> tex);

		virtual ~TextureComponent() override;
	
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& rhs) = delete;
		TextureComponent& operator=(TextureComponent&& rhs) = delete;
	private:
		std::shared_ptr<Texture2D> m_sTexture{};

		bool m_UpdateRenderer{ true };
	};
}
