#pragma once

namespace dae
{
	class GameObject;

	class MonoBehavior
	{
	public:
		virtual void FixedUpdate(){};
		virtual void Update() {};
		virtual void LateUpdate() {};

		virtual void Render() const{};
	public:
		MonoBehavior() = default; //Awake
		MonoBehavior(bool isRenderComponent) :m_IsRenderComponent{ isRenderComponent } {} //Awake
		
		virtual ~MonoBehavior();
		
		MonoBehavior(const MonoBehavior& other) = delete;
		MonoBehavior(MonoBehavior&& other) = delete;
		MonoBehavior& operator=(const MonoBehavior& rhs) = delete;
		MonoBehavior& operator=(MonoBehavior&& rhs) = delete;

		std::string ToString() const { return m_Name; }

	protected:
		friend class GameObject;
		void SetParent(UINT id) { m_ParentID = id; }
	protected:
		bool m_Enabled = true;
		std::string m_Name = "Empty";
		UINT m_ParentID{};

		const bool m_IsRenderComponent{false};
	private:
	};

	//macros


#define PARENT SCENEMANAGER.GetActiveScene()->GetObjectById(m_ParentID)
}
