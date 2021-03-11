#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class TextComponent;

	class ScoreObserver : public Observer
	{
	public:
		virtual void ScoreChanged(int value) = 0;
	};

	class ScoreObserverComponent : public BaseComponent, public ScoreObserver
	{
	public:
		ScoreObserverComponent() = default;
		~ScoreObserverComponent() override = default;
		ScoreObserverComponent(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent(ScoreObserverComponent&& other) = delete;
		ScoreObserverComponent& operator=(const ScoreObserverComponent& rhs) = delete;
		ScoreObserverComponent& operator=(ScoreObserverComponent&& rhs) = delete;

		void SetTextComponent(const std::shared_ptr<dae::TextComponent>& textComp) { m_wTextComponent = textComp; }
		void ScoreChanged(int value) override;
	private:
		std::weak_ptr<TextComponent> m_wTextComponent{};
	};
}
