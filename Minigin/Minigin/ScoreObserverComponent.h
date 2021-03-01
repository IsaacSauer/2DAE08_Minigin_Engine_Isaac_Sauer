#pragma once
#include "MonoBehavior.h"
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class TextComponent;

	class ScoreObserverComponent : public MonoBehavior, public Observer
	{
	public:
		virtual void OnNotify(std::shared_ptr<dae::GameObject> go, std::shared_ptr<EventAttributes> event) override;
	public:
		ScoreObserverComponent() = default;
		~ScoreObserverComponent() override = default;
		ScoreObserverComponent(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent(ScoreObserverComponent&& other) = delete;
		ScoreObserverComponent& operator=(const ScoreObserverComponent& rhs) = delete;
		ScoreObserverComponent& operator=(ScoreObserverComponent&& rhs) = delete;

		void SetTextComponent(const std::shared_ptr<dae::TextComponent>& textComp) { m_wTextComponent = textComp; }
	private:
		std::weak_ptr<TextComponent> m_wTextComponent{};
	};
}

