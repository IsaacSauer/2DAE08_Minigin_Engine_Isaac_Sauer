#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "GameObject.h"
#include "HealthObserverComponent.h"
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

void dae::HealthComponent::AddObserver(const std::weak_ptr<HealthObserverComponent>& add)
{
	m_Subject.AddObserver(add);
}

void dae::HealthComponent::RemoveObserver(const std::weak_ptr<HealthObserverComponent>& remove)
{
	m_Subject.RemoveObserver(remove);
}

void dae::HealthComponent::Update()
{
	//EvaluateHealth();
}

void dae::HealthComponent::Start()
{
	m_Name = GetParent()->GetName();
	EvaluateHealth();
}

dae::HealthComponent::HealthComponent()
	:BaseComponent()
{
}

void dae::HealthComponent::EvaluateHealth()
{
	for (auto& obs : m_Subject.GetObservers())
	{
		obs.lock()->LivesChanged(m_Name, m_Lives);
		//Died
		if (m_Health <= 0.f)
		{
			obs.lock()->Died(m_Name);
		}
	}
}
