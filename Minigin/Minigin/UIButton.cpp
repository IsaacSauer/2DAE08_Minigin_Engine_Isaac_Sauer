#include "MiniginPCH.h"
#include "UIButton.h"


#include "Command.h"
#include "imgui.h"

void dae::UIButton::Present(const ImGuiViewport* viewport)
{
	ImGui::SetCursorPos({ viewport->Size.x * m_Pos.x - 50, viewport->Size.y * m_Pos.y - 10 });
	m_State = ImGui::Button(m_ButtonName.c_str(), { 100, 20 });
}

void dae::UIButton::Update()
{
	if(m_State && m_Command)
	{
		m_Command->Execute();
		m_State = false;
	}
}
