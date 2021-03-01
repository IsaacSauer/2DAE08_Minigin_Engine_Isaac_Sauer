#pragma once
#include "UIElement.h"

namespace dae
{
	
	class UITextBox : public UIElement
	{
	public:
		UITextBox(const glm::vec2& pos, float width, const std::string& text);
		
		virtual void Present(const ImGuiViewport* viewport) override;
		virtual void Update() override;

		void SetText(const std::string& text) { m_Text = text; }
	public:
		virtual ~UITextBox() override;
		UITextBox(const UITextBox& other) = delete;
		UITextBox(UITextBox&& other) = delete;
		UITextBox& operator=(const UITextBox& rhs) = delete;
		UITextBox& operator=(UITextBox&& rhs) = delete;

	private:
		std::string m_Text{};
		float m_Width{};
	};
}

