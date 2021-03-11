#include "MiniginPCH.h"
#include "ScoreObserverComponent.h"

#include "ScoreComponent.h"
#include "TextComponent.h"

void dae::ScoreObserverComponent::ScoreChanged(int value)
{
	m_wTextComponent.lock()->SetText("Score: " + std::to_string(value));
}
