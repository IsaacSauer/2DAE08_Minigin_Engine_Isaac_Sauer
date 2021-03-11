#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class HealthObserver : public Observer
	{
	public:
		virtual void Died(const std::string& name) = 0;
		virtual void LivesChanged(const std::string& name, int lives) = 0;
	};

	class HealthObserverComponent : public BaseComponent, public HealthObserver
	{
	public:
		virtual void Update() override;

	public:
		HealthObserverComponent() = default;
		virtual ~HealthObserverComponent() override = default;
		HealthObserverComponent(const HealthObserverComponent& other) = delete;
		HealthObserverComponent(HealthObserverComponent&& other) = delete;
		HealthObserverComponent& operator=(const HealthObserverComponent& rhs) = delete;
		HealthObserverComponent& operator=(HealthObserverComponent&& rhs) = delete;

		void SetTextComponent(const std::shared_ptr<dae::TextComponent>& textComp) { m_wTextComponent = textComp; }

		void Died(const std::string& name) override;
		void LivesChanged(const std::string& name, int lives) override;
	private:
		std::weak_ptr<dae::TextComponent> m_wTextComponent{};
	};
}
