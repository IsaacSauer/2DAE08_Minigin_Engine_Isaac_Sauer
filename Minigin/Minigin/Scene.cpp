#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "RenderComponent2D.h"
#include "RenderComponentUI.h"

using namespace dae;

std::shared_ptr<GameObject> Scene::GetObjectById(UINT id) const
{
	std::lock_guard<std::mutex> guard(m_AccessObjectsMutex);
	START_MEASUREMENT();

	const auto result = m_Objects.find(id);
	if(result == m_Objects.end())
	{
		std::cerr << "Object not found\n";
		return std::shared_ptr<GameObject>();
	}
	return result->second;
}

std::shared_ptr<GameObject> Scene::CreateGameObjectInScene(const std::string& name)
{
	std::lock_guard<std::mutex> guard(m_AccessObjectsMutex);
	START_MEASUREMENT();

	auto go = std::make_shared<GameObject>(name);
	go->m_SceneID = m_SceneID;
	Add(go);
	return go;
}

Scene::Scene(const std::string& name, UINT id)
	: m_Name{ name }
	,m_SceneID{id}
{
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->m_SceneID = m_SceneID;
	m_Objects.insert({ object->m_ID, object});
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

void Scene::Start()
{
	for (auto& object : m_Objects)
	{
		object.second->Start();
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

