#pragma once
#include <unordered_map>
#include "Singleton.h"
#include <mutex>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, bool setAsActive = true);

		std::shared_ptr<Scene> GetActiveScene() const { return m_ActiveScene; }
		void SetActiveScene(uint32_t sceneID);

		std::shared_ptr<Scene> GetSceneByName(const std::string& name) const;
		std::shared_ptr<Scene> GetSceneById(uint32_t id) const;
		uint32_t GetIdByName(const std::string& name) const;
		
		void FixedUpdate();
		void Update();
		void Start();

		
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unordered_map<uint32_t, std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_ActiveScene{};

		static unsigned int m_SceneIdCounter;

		std::mutex m_CreateSceneMutex;
		std::mutex m_SetActiveSceneMutex;
	};

	//Macros
	#define SCENEMANAGER dae::SceneManager::GetInstance()

}
