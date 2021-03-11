#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "RenderComponent2D.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Time.h"

dae::TextureComponent::~TextureComponent() = default;

dae::TextureComponent::TextureComponent(std::shared_ptr<Texture2D> tex)
	:BaseComponent()
	,m_sTexture{tex}
{
	m_Name = "Texture2D";
}

void dae::TextureComponent::FixedUpdate()
{
}

void dae::TextureComponent::Update()
{
	if(m_UpdateRenderer)
	{
		const auto result = GetParent()->GetComponentOfType<RenderComponent2D>();
		if(result)
		{
			result->RequestRender(m_sTexture);
		}
	}
}
