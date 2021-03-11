#include "MiniginPCH.h"
#include "BaseComponent.h"

#include "Command.h"

dae::BaseComponent::~BaseComponent() = default;

std::shared_ptr<dae::GameObject> dae::BaseComponent::GetParent() const
{
	return SCENEMANAGER.GetSceneById(m_SceneID)->GetObjectById(m_ParentID);
}
