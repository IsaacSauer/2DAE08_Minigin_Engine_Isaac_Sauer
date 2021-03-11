#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class ScoreObserverComponent;
	class ScoreComponent : public BaseComponent
	{
	public:
		int GetScore() const;
		void SetScore(int value);
		void AddScore(int value);
	public:
		void AddObserver(const std::weak_ptr<ScoreObserverComponent>& add);
		void RemoveObserver(const std::weak_ptr<ScoreObserverComponent>& remove);
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

		Subject<ScoreObserverComponent> m_Subject;
	};
}
