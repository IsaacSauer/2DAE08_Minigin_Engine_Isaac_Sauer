#pragma once
#include <iostream>

#include "GameObject.h"
#include "HealthComponent.h"
#include "Scene.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

class Command
{
public:
	Command() = default;
	Command(std::weak_ptr<dae::GameObject> targetObj):m_TargetGameObject{targetObj}{};

	//Command(const Command& other) = delete;
	//Command(Command&& other) = delete;
	//const Command& operator=(const Command& rhs) = delete;
	//const Command& operator=(Command&& rhs) = delete;

	virtual ~Command() = default;
	virtual void Execute() = 0;
protected:
	std::weak_ptr<dae::GameObject> GetGameObject() { return m_TargetGameObject; }
private:
	std::weak_ptr<dae::GameObject> m_TargetGameObject{};
};

///////////////////////////////
//SCENE SWITCH COMMANDS
///////////////////////////////
class ActivateMenu final : public Command
{
public:
	void Execute() override
	{
		SCENEMANAGER.SetActiveScene(SCENEMANAGER.GetIdByName("Menu"));
	}
};
class ActivateSingleplayer final : public Command
{
public:
	void Execute() override
	{
		SCENEMANAGER.SetActiveScene(SCENEMANAGER.GetIdByName("Singleplayer"));
	}
};
class ActivateCoop final : public Command
{
public:
	void Execute() override
	{
		SCENEMANAGER.SetActiveScene(SCENEMANAGER.GetIdByName("Coop"));
	}
};
class ActivateVersus final : public Command
{
public:
	void Execute() override
	{
		SCENEMANAGER.SetActiveScene(SCENEMANAGER.GetIdByName("Versus"));
	}
};



///////////////////////////////
class Fire final : public Command
{
public:
	void Execute() override
	{
		std::cout << "Fire!\n";
	}
};
class Duck final : public Command
{
public:
	void Execute() override
	{
		std::cout << "Duck!\n";
	}
};
class Jump final : public Command
{
public:
	void Execute() override
	{
		std::cout << "Jump!\n";
	}
};
class Fart final : public Command
{
public:
	void Execute() override
	{
		std::cout << "Fart!\n";
	}
};

class ChangeText final : public Command
{
public:
	ChangeText(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};

	void Execute() override
	{
		GetGameObject().lock()->GetComponentOfType<dae::TextComponent>()->SetText("LOOLOLOL");
	}
};

class ChangeColor final : public Command
{
public:
	ChangeColor(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};

	void Execute() override
	{
		GetGameObject().lock()->GetComponentOfType<dae::ScoreComponent>()->AddScore(25);
	}
};
class DefeatCoilyWithFlyingDisc final : public Command
{
public:
	DefeatCoilyWithFlyingDisc(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};
	void Execute() override
	{
		GetGameObject().lock()->GetComponentOfType<dae::ScoreComponent>()->AddScore(500);
	}
};
class RemainingDiscsAtTheEndOfAStage final : public Command
{
public:
	RemainingDiscsAtTheEndOfAStage(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};
	void Execute() override
	{
		GetGameObject().lock()->GetComponentOfType<dae::ScoreComponent>()->AddScore(50);
	}
};
class CatchSlickAndSam final : public Command
{
public:
	CatchSlickAndSam(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};
	void Execute() override
	{
		GetGameObject().lock()->GetComponentOfType<dae::ScoreComponent>()->AddScore(300);
	}
};

class Kill final : public Command
{
public:
	Kill(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};

	void Execute() override
	{
		if(auto health = GetGameObject().lock()->GetComponentOfType<dae::HealthComponent>())
		{
			health->SetHealth(-1.f);
		}
	}
};
class Respawn final : public Command
{
public:
	Respawn(std::weak_ptr<dae::GameObject> targetObj) :Command(targetObj) {};

	void Execute() override
	{
		if(auto health = GetGameObject().lock()->GetComponentOfType<dae::HealthComponent>())
		{
			if(health->GetHealth() <= 0.f && health->GetLives() > 0)
			{
				health->SetHealth(health->GetMaxHealth());
				health->AddLives(-1);
			}
		}
	}
};