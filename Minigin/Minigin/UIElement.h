#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct ImGuiViewport;

namespace dae
{
	class UIElement
	{
	public:

#pragma warning(push)
#pragma warning (disable:4100)
		virtual void Present(const ImGuiViewport* viewport){};
#pragma warning(pop)

		virtual void Update(){};
		
		UIElement() = default;
		UIElement(const glm::vec2& pos):m_Pos{pos}{}

	public:
		virtual ~UIElement() = default;
		UIElement(const UIElement& other) = delete;
		UIElement(UIElement&& other) = delete;
		const UIElement& operator=(const UIElement& rhs) = delete;
		const UIElement& operator=(UIElement&& rhs) = delete;
	protected:

		//fraction values
		glm::vec2 m_Pos{};

		//
	};
}
