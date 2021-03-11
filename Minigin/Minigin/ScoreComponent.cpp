#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "Command.h"
#include "ScoreObserverComponent.h"

void dae::ScoreComponent::EvaluateScore()
{
	for(auto obs : m_Subject.GetObservers())
	{
		obs.lock()->ScoreChanged(m_Score);
	}
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

void dae::ScoreComponent::AddObserver(const std::weak_ptr<ScoreObserverComponent>& add)
{
	m_Subject.AddObserver(add);
}

void dae::ScoreComponent::RemoveObserver(const std::weak_ptr<ScoreObserverComponent>& remove)
{
	m_Subject.RemoveObserver(remove);
}
