#pragma once
#include <Minigin.h>

class QBertGame : public dae::Minigin
{
public:
	virtual ~QBertGame() override = default;
	virtual void LoadGame() const override;
};

