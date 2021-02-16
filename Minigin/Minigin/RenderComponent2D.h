#pragma once
#include <SDL_render.h>

#include "MonoBehavior.h"

namespace dae
{
	class Texture2D;

	class RenderComponent2D : public dae::MonoBehavior
	{
	public:
		void RequestRender(std::shared_ptr<Texture2D> tex) { m_sTextureToRender = tex; }

		void Render() const;
	public:
		RenderComponent2D();
		RenderComponent2D(std::shared_ptr<Texture2D> componentToRender);

		virtual ~RenderComponent2D() override;
		
		RenderComponent2D(const RenderComponent2D& other) = delete;
		RenderComponent2D(RenderComponent2D&& other) = delete;
		RenderComponent2D& operator=(const RenderComponent2D& rhs) = delete;
		RenderComponent2D& operator=(RenderComponent2D&& rhs) = delete;
	private:

		std::shared_ptr<Texture2D> m_sTextureToRender{};
	};
	
}
