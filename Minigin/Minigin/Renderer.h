#pragma once
#include <SDL_video.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		static glm::vec2 GetCurrentWindowDimensions()
		{
			int w{};
			int h{};
			SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &w, &h);
			return { w, h };
		}
	private:
		SDL_Renderer* m_Renderer{};
	};

	//Macros
#define RENDERER dae::Renderer::GetInstance()
}

