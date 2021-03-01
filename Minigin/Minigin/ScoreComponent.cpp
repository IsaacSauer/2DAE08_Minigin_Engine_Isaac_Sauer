#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "Command.h"

void dae::ScoreComponent::EvaluateScore()
{
	auto scoreAttributes = std::make_shared<ScoreEventAttributes>();
	scoreAttributes->score = m_Score;
	Notify(PARENT->shared_from_this(), scoreAttributes);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}

void dae::ScoreComponent::SetScore(int value)
{
	m_Score = value;
	EvaluateScore();
}

void dae::ScoreComponent::AddScore(int value)
{
	m_Score += value;
	EvaluateScore();
}
