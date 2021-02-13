#pragma once
#include "MonoBehavior.h"
#include "SceneManager.h"
#include "Singleton.h"
#include "TextureComponent.h"

namespace dae
{
	class Timer : public Singleton<Timer>
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
#define TIMER dae::Timer::GetInstance()

}
