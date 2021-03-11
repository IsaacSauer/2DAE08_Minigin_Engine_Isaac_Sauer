#include "MiniginPCH.h"
#include "RenderComponent2D.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "Texture2D.h"

void dae::RenderComponent2D::Render() const
{
	if(m_sTextureToRender)
	{
		auto transform = GetParent()->GetTransform();
		RENDERER.RenderTexture(*m_sTextureToRender.get(), transform.GetPosition().x, transform.GetPosition().y);
	}
}

dae::RenderComponent2D::RenderComponent2D()
	:BaseComponent(true)
{
}


dae::RenderComponent2D::RenderComponent2D(std::shared_ptr<Texture2D> texToRender)
	:BaseComponent()
	, m_sTextureToRender{texToRender}
{
}

dae::RenderComponent2D::~RenderComponent2D() = default;
