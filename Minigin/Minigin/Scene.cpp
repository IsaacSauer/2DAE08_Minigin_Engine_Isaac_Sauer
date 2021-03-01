#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent2D.h"
#include "RenderComponentUI.h"

using namespace dae;

std::shared_ptr<GameObject> Scene::GetObjectById(UINT id) const
{
	const auto result = m_Objects.find(id);
	if(result == m_Objects.end())
	{
		std::cerr << "Object not found\n";
		return std::shared_ptr<GameObject>();
	}
	return result->second;
}

Scene::Scene(const std::string& name, UINT id)
	: m_Name{ name }
	,m_SceneID{id}
{
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.insert({GameObject::m_GameObjectIdCounter, object});
	GameObject::m_GameObjectIdCounter++;
}

void Scene::FixedUpdate()
{
	for(auto& object : m_Objects)
	{
		object.second->FixedUpdate();
	}
}

void Scene::Update()
{
	for (auto& object : m_Objects)
	{
		object.second->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		//RenderComponents2D
		auto renderComponents2D = object.second->GetAllComponentsOfType<RenderComponent2D>();
		for (const auto element : renderComponents2D)
		{
			element->Render();
		}
		
		//RenderComponentsUI
		auto renderComponentsUI = object.second->GetAllComponentsOfType<RenderComponentUI>();
		for (const auto element : renderComponentsUI)
		{
			element->Render();
		}
	}
}

