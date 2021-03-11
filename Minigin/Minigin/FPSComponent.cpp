#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "Time.h"
#include "TextComponent.h"

void dae::FPSComponent::Update()
{
	m_Interval -= TIME.ElapsedSec();
	if (m_Interval <= 0.f)
	{
		m_wTextComponent.lock()->SetText("FPS:" + std::to_string(1.f / TIME.ElapsedSec()));
		m_Interval = 1.f;
		m_FramesCounted = 0;
	}
	else
		++m_FramesCounted;
}
