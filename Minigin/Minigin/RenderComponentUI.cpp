#include "MiniginPCH.h"
#include "RenderComponentUI.h"

#include "UIElement.h"

void dae::RenderComponentUI::Render() const
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = 4.f;
	style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
	style.WindowBorderSize = 0.f;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(m_Use_Work_Area ? viewport->WorkPos : viewport->Pos);
	ImGui::SetNextWindowSize(m_Use_Work_Area ? viewport->WorkSize : viewport->Size);

	if (ImGui::Begin(m_Name.c_str(), {}, m_Flags))
	{
		for(auto& element : m_UIElements)
		{
			element->Present(viewport);
		}
	}
	ImGui::End();

}

void dae::RenderComponentUI::Update()
{
	for (auto& element : m_UIElements)
	{
		element->Update();
	}
}

void dae::RenderComponentUI::AddUIElement(std::shared_ptr<UIElement> element)
{
	m_UIElements.push_back(element);
}

dae::RenderComponentUI::RenderComponentUI(const std::vector<std::shared_ptr<UIElement>>& elements, const std::string& name)
	:m_UIElements(elements)
	,m_Name(name)
{
}
