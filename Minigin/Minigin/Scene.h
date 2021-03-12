#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, bool setAsActive);
	public:

		void FixedUpdate();
		void Update();
		void Start();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		UINT GetSceneID() const { return m_SceneID; }
		const std::string& GetName() const { return m_Name; }

		std::shared_ptr<GameObject> GetObjectById(UINT id) const;

		std::shared_ptr<GameObject> CreateGameObjectInScene(const std::string& name);
	private: 
		void Add(const std::shared_ptr<GameObject>& object);


		explicit Scene(const std::string& name, UINT id);

		std::string m_Name{};
		std::unordered_map<UINT ,std::shared_ptr<GameObject>> m_Objects{};


		UINT m_SceneID{};

		mutable std::mutex m_AccessObjectsMutex{};
	};

}
