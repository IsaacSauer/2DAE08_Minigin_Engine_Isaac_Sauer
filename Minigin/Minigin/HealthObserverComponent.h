#pragma once
#include "MonoBehavior.h"
#include "Observer.h"
#include "TextComponent.h"

class HealthObserverComponent : public dae::MonoBehavior, public dae::Observer
{
public:
	virtual void Update() override;

public:
	virtual void OnNotify(std::shared_ptr<dae::GameObject> go, int event) override;
	
public:
	HealthObserverComponent() = default;
	virtual ~HealthObserverComponent() override = default;
	HealthObserverComponent(const HealthObserverComponent& other) = delete;
	HealthObserverComponent(HealthObserverComponent&& other) = delete;
	HealthObserverComponent& operator=(const HealthObserverComponent& rhs) = delete;
	HealthObserverComponent& operator=(HealthObserverComponent&& rhs) = delete;

	void SetTextComponent(const std::shared_ptr<dae::TextComponent>& textComp) { m_wTextComponent = textComp; }
private:
	std::weak_ptr<dae::TextComponent> m_wTextComponent{};

};
