#include "MiniginPCH.h"
#include "SceneManager.h"


#include "InputManager.h"
#include "Scene.h"

unsigned int dae::SceneManager::m_SceneIdCounter = 0;

void dae::SceneManager::SetActiveScene(UINT sceneID)
{
	std::lock_guard<std::mutex> guard(m_SetActiveSceneMutex);
	START_MEASUREMENT();

	const auto foundScene = GetSceneById(sceneID);
	if (!foundScene)
		std::cerr << "Could not enable that scene.\n";
	else
	{
		m_ActiveScene = foundScene;
		m_ActiveScene->Start();
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetSceneByName(const std::string& name) const
{
	const auto foundScene = std::find_if(m_Scenes.begin(), m_Scenes.end(),
		[&name](const std::pair<UINT, std::shared_ptr<Scene>>& A)
		{ return A.second->GetName() == name; });

	if (foundScene == m_Scenes.end())
	{
		std::cerr << "Requested scene not found\n";
		return std::shared_ptr<Scene>();
	}

	return foundScene->second;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetSceneById(UINT id) const
{
	const auto requested = m_Scenes.find(id);
	if (requested == m_Scenes.end())
	{
		std::cerr << "Requested scene not found\n";
		return std::shared_ptr<Scene>();
	}
	return requested->second;
}

UINT dae::SceneManager::GetIdByName(const std::string& name) const
{
	const auto foundScene = std::find_if(m_Scenes.begin(), m_Scenes.end(),
		[&name](const std::pair<UINT, std::shared_ptr<Scene>>& A)
		{ return A.second->GetName() == name; });

	if (foundScene == m_Scenes.end())
	{
		std::cerr << "Requested scene not found\n";
		return 0;
	}

	return foundScene->first;
}

void dae::SceneManager::FixedUpdate()
{
	m_ActiveScene->FixedUpdate();
}

void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
}

void dae::SceneManager::Start()
{
	m_ActiveScene->Start();
}

void dae::SceneManager::Render() const
{
	m_ActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name, bool setAsActive)
{
	std::lock_guard<std::mutex> guard(m_CreateSceneMutex);
	START_MEASUREMENT();

	const auto& scene = std::shared_ptr<Scene>(new Scene(name, m_SceneIdCounter));
	m_Scenes.insert({ m_SceneIdCounter, scene });
	if (setAsActive)
		m_ActiveScene = scene;

	++m_SceneIdCounter;
	return *scene;
}