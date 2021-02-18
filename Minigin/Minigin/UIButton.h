#pragma once
#include "UIElement.h"

class Command;

namespace dae
{
	class UIButton : public UIElement
	{
	public:
		void Present(const ImGuiViewport* viewport) override;
		void Update() override;

		template <typename T>
		UIButton(const glm::vec2& pos, std::unique_ptr<T> upCommand, const std::string& name);
	public:
		virtual ~UIButton() = default;
		UIButton(const UIButton& other) = delete;
		UIButton(UIButton&& other) = delete;
		const UIButton& operator=(const UIButton& rhs) = delete;
		const UIButton& operator=(UIButton&& rhs) = delete;

	private:
		std::string m_ButtonName;
		bool m_State{ false };
		std::unique_ptr<Command> m_Command{};
	};

	template <typename T>
	UIButton::UIButton(const glm::vec2& pos, std::unique_ptr<T> upCommand, const std::string& name)
		:UIElement(pos)
		,m_ButtonName(name)
	{
		m_Command = std::move(upCommand);
	}
}
