#include "MiniginPCH.h"
#include "HealthObserverComponent.h"

#include "HealthComponent.h"

void HealthObserverComponent::Update()
{
}

void HealthObserverComponent::OnNotify(std::shared_ptr<dae::GameObject> go, std::shared_ptr<dae::EventAttributes> event)
{
	if(auto cast = std::dynamic_pointer_cast<dae::HealthEventAttributes>(event))
	{
		switch (cast->state)
		{
		case dae::HealthEventAttributes::HealthState::DIED:
			m_wTextComponent.lock()->SetText("PlayerDied");
			break;
		case dae::HealthEventAttributes::HealthState::ALLIVE:
			m_wTextComponent.lock()->SetText("Remaining lives: " + std::to_string(cast->lives));
			break;
		}
	}
}
