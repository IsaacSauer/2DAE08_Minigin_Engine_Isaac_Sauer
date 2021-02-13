#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "Font.h"
#include "GameObject.h"
#include "RenderComponent2D.h"
#include "Renderer.h"
#include "Scene.h"
#include "Texture2D.h"

dae::TextComponent::~TextComponent() = default;

void dae::TextComponent::SetText(const std::string& text)
{
	m_NeedsUpdate = true;
	m_Text = text;
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_sFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_sTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;

		const auto result = PARENT->GetComponentOfType<RenderComponent2D>();
		if (result)
		{
			result->RequestRender(m_sTexture);
		}
	}
}

dae::TextComponent::TextComponent(const std::shared_ptr<Font>& font)
	:m_sFont{font}
{

}
