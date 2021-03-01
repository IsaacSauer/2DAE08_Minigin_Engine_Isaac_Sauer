#pragma once

#include "imgui.h"

#include "MonoBehavior.h"

namespace dae
{
	class UIElement;

	class RenderComponentUI : public MonoBehavior
	{
	public:
		RenderComponentUI() = default;
		RenderComponentUI(const std::vector<std::shared_ptr<UIElement>>& elements, const std::string& name = "Untitled");

		void Render() const;
		void Update() override;

		void AddUIElement(std::shared_ptr<UIElement> element);
		void SetRenderFlags(ImGuiWindowFlags flags) { m_Flags = flags; }

	public:
		virtual ~RenderComponentUI() override = default;
		
		RenderComponentUI(const RenderComponentUI& other) = delete;
		RenderComponentUI(RenderComponentUI&& other) = delete;
		const RenderComponentUI& operator=(const RenderComponentUI& other) = delete;
		const RenderComponentUI& operator=(RenderComponentUI&& other) = delete;
	private:
		ImGuiWindowFlags m_Flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		bool m_Use_Work_Area = true;
		std::string m_Name{"Placeholder"};

		std::vector<std::shared_ptr<UIElement>> m_UIElements{};
	};
}
