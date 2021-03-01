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

		void SetAutoSize(bool autoSize) { m_AutoSize = autoSize; }

		template <typename T>
		UIButton(const glm::vec2& pos, std::unique_ptr<T> upCommand, const std::string& name, bool autoSize = true);
	public:
		virtual ~UIButton() = default;
		UIButton(const UIButton& other) = delete;
		UIButton(UIButton&& other) = delete;
		UIButton& operator=(const UIButton& rhs) = delete;
		UIButton& operator=(UIButton&& rhs) = delete;

	private:
		std::string m_ButtonName;
		bool m_State{ false };
		std::unique_ptr<Command> m_Command{};

		bool m_AutoSize = true;
	};

	template <typename T>
	UIButton::UIButton(const glm::vec2& pos, std::unique_ptr<T> upCommand, const std::string& name, bool autoSize)
		:UIElement(pos)
		, m_ButtonName(name)
		, m_AutoSize(autoSize)
	{
		m_Command = std::move(upCommand);
	}
}
