#pragma once
#include <memory>
#include <string>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		virtual void FixedUpdate(){};
		virtual void Update() {};

		virtual void Start() {};
	public:
		BaseComponent() = default; //Awake
		BaseComponent(bool isRenderComponent) :m_IsRenderComponent{ isRenderComponent } {} //Awake
		
		virtual ~BaseComponent();
		
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& rhs) = delete;
		BaseComponent& operator=(BaseComponent&& rhs) = delete;

		std::string ToString() const { return m_Name; }

		std::shared_ptr<GameObject> GetParent() const;
	protected:
		friend class GameObject;
		void SetParent(uint32_t id) { m_ParentID = id; }
		void SetScene(uint32_t id) { m_SceneID = id; };
	protected:
		bool m_Enabled = true;
		std::string m_Name = "Empty";
		uint32_t m_ParentID{};
		uint32_t m_SceneID{};
		const bool m_IsRenderComponent{false};
	private:
	};
}
