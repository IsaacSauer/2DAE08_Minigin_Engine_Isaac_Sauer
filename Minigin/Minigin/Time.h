#pragma once
#include "Singleton.h"

namespace dae
{
	class Time : public Singleton<Time>
	{
	public:
		float ElapsedSec() const { return dTime; };
		float FixedTimeStep() const { return fixedTimeStep; }

	protected:
		friend class Minigin;
		void SetDeltaTime(float val) { dTime = val; }
		void SetFixedTimeStep(float val) { fixedTimeStep = val; }

	private:

		float dTime{};
		float fixedTimeStep{};
	};
	//Macros
#define TIME dae::Time::GetInstance()
}
