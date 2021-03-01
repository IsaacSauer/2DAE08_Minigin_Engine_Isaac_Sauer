#pragma once
#include "MonoBehavior.h"
#include "Subject.h"

namespace dae
{
	class HealthEventAttributes : public EventAttributes
	{
	public:
		enum class HealthState
		{
			DIED = 0,
			ALLIVE = 1,
		};

		float health{};
		float maxHealth{};
		int lives{};
		HealthState state{};
		std::string name{};
	};
	
	class HealthComponent : public MonoBehavior, public Subject
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
	public:
		virtual void Update() override;

	public:
		HealthComponent() = default;
		virtual ~HealthComponent() override = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& rhs) = delete;
		HealthComponent& operator=(HealthComponent&& rhs) = delete;
	private:
		float m_Health{20.f};
		float m_MaxHealth{20.f};
		int m_Lives{ 3 };
		void EvaluateHealth();
	};
}
