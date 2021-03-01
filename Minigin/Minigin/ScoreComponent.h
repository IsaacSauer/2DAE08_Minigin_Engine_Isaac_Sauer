#pragma once
#include "MonoBehavior.h"
#include "Subject.h"

namespace dae
{
	class ScoreEventAttributes : public EventAttributes
	{
	public:
		int score{};
	};
	
	class ScoreComponent : public dae::MonoBehavior, public dae::Subject
	{
	public:
		int GetScore() const;
		void SetScore(int value);
		void AddScore(int value);
	public:
		ScoreComponent() = default;
		virtual ~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& rhs) = delete;
		ScoreComponent& operator=(ScoreComponent&& rhs) = delete;

	private:
		int m_Score{};

		void EvaluateScore();
	};
}

