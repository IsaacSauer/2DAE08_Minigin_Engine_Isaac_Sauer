#pragma once
#include "Transform.h"
#include "unordered_map"

namespace dae
{
	class MonoBehavior;
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
		friend class Scene;
	public:
		void FixedUpdate();
		void Update();

		GameObject();
		GameObject(const std::string& name);

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		std::shared_ptr<GameObject> GetShared();
	public:
		bool AddComponent(std::shared_ptr<MonoBehavior> component);

		UINT GetID() const;
		UINT GetSceneID() const;
		
		const Transform& GetTransform() const { return m_Transform; }
		void SetTransform(const Transform& transform) { m_Transform = transform; }

		std::string ToString() const { return m_Name; }

		template <typename T>
		std::shared_ptr<T> GetComponentOfType() const;
		template <typename T>
		std::vector<std::shared_ptr<T>> GetAllComponentsOfType() const;
	private:
		void SetName(const std::string& name) { m_Name = name; }
		void SetID(UINT id) { m_ID = id; }

		
		Transform m_Transform;
		std::string m_Name = "GameObject";
		UINT m_ID{};

		UINT m_SceneID{};
		
		bool m_Enabled = true;
		
		static unsigned int m_GameObjectIdCounter;

		//Components
		std::unordered_map<UINT, std::shared_ptr<MonoBehavior>> m_Components{};
	};

	template <typename T>
	std::shared_ptr<T> GameObject::GetComponentOfType() const
	{
		auto result = std::find_if(m_Components.begin(), m_Components.end(),
			[](const std::pair<UINT, std::shared_ptr<MonoBehavior>>& A)
			{
				return std::dynamic_pointer_cast<T>(A.second);
			});
		if (result != m_Components.end())
			return std::dynamic_pointer_cast<T>(result->second);

		return std::shared_ptr<T>();
	}

	template <typename T>
	std::vector<std::shared_ptr<T>> GameObject::GetAllComponentsOfType() const
	{
		std::vector<std::shared_ptr<T>> collection{};
		for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
		{
			it = std::find_if(it, m_Components.end(), [](const std::pair<UINT, std::shared_ptr<MonoBehavior>>& A)
				{
					return std::dynamic_pointer_cast<T>(A.second);
				});

			if (it == m_Components.end())
				break;

			collection.push_back(std::dynamic_pointer_cast<T>(it->second));
		}

		return collection;
	}
}
