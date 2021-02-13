#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent2D.h"

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

Scene::Scene(const std::string& name)
	: m_Name{ name }
{
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.insert({(UINT)m_Objects.size(), object});
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
		auto renderComponents = object.second->GetAllComponentsOfType<RenderComponent2D>();
		for (const auto element : renderComponents)
		{
			element->Render();
		}
	}
}

