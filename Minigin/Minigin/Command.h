#pragma once
#include <iostream>

#include "GameObject.h"
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