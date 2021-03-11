#pragma once
#include "BaseComponent.h"


namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent : public dae::BaseComponent
	{
	public:
		virtual void FixedUpdate() override{};
		virtual void Update() override;
	public:
		TextComponent(const std::shared_ptr<Font>& font);
	
		virtual ~TextComponent() override;
	
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& rhs) = delete;
		TextComponent& operator=(TextComponent&& rhs) = delete;

		void SetText(const std::string& text);
	protected:
	private:
		bool m_NeedsUpdate{ true };

		std::string m_Text{"Placeholder"};
		std::shared_ptr<Font> m_sFont{};
		std::shared_ptr<Texture2D> m_sTexture{};
	};
	
}
