#include "MiniginPCH.h"
#include "UITextBox.h"

#include "imgui.h"

dae::UITextBox::UITextBox(const glm::vec2& pos, float width, const std::string& text)
	:UIElement(pos)
	,m_Text(text)
	,m_Width(width)
{
}

void dae::UITextBox::Present(const ImGuiViewport* viewport)
{
    ImGui::SetCursorPos({ viewport->Size.x * m_Pos.x, viewport->Size.y * m_Pos.y });
    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + m_Width);

    ImGui::TextWrapped(m_Text.c_str());

    ImGui::PopTextWrapPos();
}

void dae::UITextBox::Update()
{
}

dae::UITextBox::~UITextBox()
{
}
