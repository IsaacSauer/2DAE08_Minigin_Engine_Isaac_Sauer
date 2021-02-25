#include "MiniginPCH.h"
#include "HealthObserverComponent.h"

#include "HealthComponent.h"

void HealthObserverComponent::Update()
{
}

void HealthObserverComponent::OnNotify(std::shared_ptr<dae::GameObject> go, int event)
{
	if (event < 0) event = 0;

	auto state = static_cast<dae::HealthComponent::HealthState>(bool(event));
	if(m_wTextComponent.lock())
	{
		switch (state)
		{
		case dae::HealthComponent::HealthState::DIED:
			m_wTextComponent.lock()->SetText("PlayerDied");
			break;
			case dae::HealthComponent::HealthState::ALLIVE:
			m_wTextComponent.lock()->SetText("Remaining lives: " + std::to_string(event));
			break;
		}
	}
}
