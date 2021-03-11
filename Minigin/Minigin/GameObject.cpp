#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"

unsigned int dae::GameObject::m_GameObjectIdCounter = 0;
std::mutex dae::GameObject::m_AddComponentMutex{};

dae::GameObject::~GameObject() = default;

std::shared_ptr<dae::GameObject> dae::GameObject::GetShared()
{
	return shared_from_this();
}

bool dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	std::lock_guard<std::mutex> guard(m_AddComponentMutex);
	START_MEASUREMENT();

	if(component)
	{
		const auto result = m_Components.insert(std::make_pair((UINT)m_Components.size(), component));
		if(result.second)
		{
			result.first->second->SetParent(m_ID);
			result.first->second->SetScene(m_SceneID);
			return true;
		}
	}

	return false;
}

UINT dae::GameObject::GetSceneID() const
{
	return m_SceneID;
}

void dae::GameObject::FixedUpdate()
{
	for(auto& element : m_Components)
	{
		if(element.second->m_Enabled)
			element.second->FixedUpdate();
	}
}

void dae::GameObject::Update()
{
	for (auto& element : m_Components)
	{
		if (element.second->m_Enabled)
			element.second->Update();
	}
}

void dae::GameObject::Start()
{
	for (auto& element : m_Components)
	{
		if (element.second->m_Enabled)
			element.second->Start();
	}
}

dae::GameObject::GameObject()
{
	m_ID = m_GameObjectIdCounter;
	m_GameObjectIdCounter++;
}

dae::GameObject::GameObject(const std::string& name)
	:GameObject()
{
	m_Name = name;
}

//void dae::GameObject::Render() const
//{
//	for(auto it = m_Components.begin(); it != m_Components.end(); ++it)
//	{
//		it = std::find_if(it, m_Components.end(), [](const std::pair<UINT, std::shared_ptr<MonoBehavior>>& A)
//		{
//				return A.second->m_IsRenderComponent && A.second->m_Enabled;
//		});
//
//		if (it == m_Components.end())
//			break;
//
//		it->second->Render();
//	}
//}
