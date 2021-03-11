#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthObserverComponent;
	class HealthComponent : public BaseComponent
	{
	public:

		void AddHealth(float delta);
		void SetHealth(float value);
		float GetHealth() const;
		void SetMaxHealth(float value);
		float GetMaxHealth() const;
		void AddLives(int delta);
		void SetLives(int value);
		int GetLives() const;

		void AddObserver(const std::weak_ptr<HealthObserverComponent>& add);
		void RemoveObserver(const std::weak_ptr<HealthObserverComponent>& remove);
	public:
		virtual void Update() override;
		virtual void Start() override;
	public:
		HealthComponent();
		virtual ~HealthComponent() override = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& rhs) = delete;
		HealthComponent& operator=(HealthComponent&& rhs) = delete;
	private:
		float m_Health{ 20.f };
		float m_MaxHealth{ 20.f };
		int m_Lives{ 3 };
		void EvaluateHealth();

		Subject<HealthObserverComponent> m_Subject;
	};
}
