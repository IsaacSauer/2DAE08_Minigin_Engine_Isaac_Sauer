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

void dae::HealthComponent::AddLives(int delta)
{
	m_Lives += delta;
	EvaluateHealth();
}

void dae::HealthComponent::SetLives(int value)
{
	m_Lives = value;
	EvaluateHealth();
}

int dae::HealthComponent::GetLives() const
{
	return m_Lives;
}

void dae::HealthComponent::Update()
{
	//EvaluateHealth();
}

void dae::HealthComponent::EvaluateHealth()
{
	auto healthAttributes = std::make_shared<HealthEventAttributes>();
	healthAttributes->health = m_Health;
	healthAttributes->maxHealth = m_MaxHealth;
	healthAttributes->lives = m_Lives;
	healthAttributes->state = HealthEventAttributes::HealthState(m_Health > 0.f);
	Notify(PARENT->shared_from_this(), healthAttributes);
}