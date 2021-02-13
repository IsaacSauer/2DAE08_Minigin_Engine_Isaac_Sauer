#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "Timer.h"
#include "TextComponent.h"

void dae::FPSComponent::Update()
{
	m_Interval -= TIMER.ElapsedSec();
	if (m_Interval <= 0.f)
	{
		m_wTextComponent.lock()->SetText("FPS:" + std::to_string(1.f / TIMER.ElapsedSec()));
		m_Interval = 1.f;
		m_FramesCounted = 0;
	}
	else
		++m_FramesCounted;
}
