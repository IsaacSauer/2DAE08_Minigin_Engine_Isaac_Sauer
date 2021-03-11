#include "MiniginPCH.h"
#include "HealthObserverComponent.h"

#include "HealthComponent.h"

void dae::HealthObserverComponent::Update()
{
}

void dae::HealthObserverComponent::Died(const std::string& name)
{
	m_wTextComponent.lock()->SetText(name + " died");
}

void dae::HealthObserverComponent::LivesChanged(const std::string& name, int lives)
{
	m_wTextComponent.lock()->SetText(name + " remaining lives: " + std::to_string(lives));
}
