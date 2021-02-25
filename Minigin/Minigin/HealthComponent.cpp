#include "MiniginPCH.h"
#include "HealthComponent.h"


#include "GameObject.h"
#include "Scene.h"

void dae::HealthComponent::AddHealth(float delta)
{
	m_Health += delta;
	EvaluateHealth();
}

void dae::HealthComponent::SetHealth(float value)
{
	m_Health = value;
	EvaluateHealth();
}

float dae::HealthComponent::GetHealth() const
{
	return m_Health;
}

void dae::HealthComponent::SetMaxHealth(float value)
{
	m_MaxHealth = value;
}

float dae::HealthComponent::GetMaxHealth() const
{
	return m_MaxHealth;
}

void dae::HealthComponent::Update()
{
	EvaluateHealth();
}

void dae::HealthComponent::EvaluateHealth()
{
	if (m_Health <= 0)
	{
		Notify(PARENT->shared_from_this(), HealthState::DIED);

		m_Health = m_MaxHealth;
		--m_Lives;
	}
	else
	{
		Notify(PARENT->shared_from_this(), m_Lives);

	}
}
