#include "MiniginPCH.h"
#include "ScoreObserverComponent.h"

#include "ScoreComponent.h"
#include "TextComponent.h"

void dae::ScoreObserverComponent::OnNotify(std::shared_ptr<dae::GameObject> go, std::shared_ptr<EventAttributes> event)
{
	if(auto cast = std::dynamic_pointer_cast<ScoreEventAttributes>(event))
	{
		m_wTextComponent.lock()->SetText("Score: " + std::to_string(cast->score));
	}
}
