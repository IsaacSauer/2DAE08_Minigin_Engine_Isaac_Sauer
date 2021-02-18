#pragma once
#include <unordered_map>


#include "imgui.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, bool setAsActive = true);

		std::shared_ptr<Scene> GetActiveScene() const { return m_ActiveScene; }
		void SetActiveScene(UINT sceneID);

		std::shared_ptr<Scene> GetSceneByName(const std::string& name) const;
		std::shared_ptr<Scene> GetSceneById(UINT id) const;
		
		void FixedUpdate();
		void Update();
		
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unordered_map<UINT, std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_ActiveScene{};

		static unsigned int m_SceneIdCounter;
	};

	//Macros
	#define SCENEMANAGER dae::SceneManager::GetInstance()

	//inline void ShowMenu(bool* p_open)
	//{
	//	ImGuiStyle& style = ImGui::GetStyle();
	//	style.FrameRounding = 4.f;
	//	style.WindowBorderSize = 0.f;
	//	
	//	static bool use_work_area = true;
	//	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

	//	// We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
	//	// Based on your use case you may want one of the other.
	//	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	//	ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
	//	ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

	//	
	//	if (ImGui::Begin("MainMenu", p_open, flags))
	//	{
	//		//ImGui::SetWindowFontScale(1.5);
	//		ImGui::SetCursorPos({ viewport->Size.x / 2 - 50, viewport->Size.y / 2 - 25});
	//		if (p_open && ImGui::Button("Singleplayer", {100, 20}))
	//			*p_open = false;
	//		ImGui::SetCursorPos({ viewport->Size.x / 2 - 50, viewport->Size.y / 2});
	//		if (p_open && ImGui::Button("Co-op", {100, 20}))
	//			*p_open = false;
	//		ImGui::SetCursorPos({ viewport->Size.x / 2 - 50, viewport->Size.y / 2 + 25});
	//		if (p_open && ImGui::Button("Versus", {100, 20}))
	//			*p_open = false;
	//	}
	//	ImGui::End();
	//}

}
