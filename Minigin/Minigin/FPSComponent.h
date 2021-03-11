#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;

	class FPSComponent : public dae::BaseComponent
	{
	public:
		void Update() override;

	public:
		FPSComponent() = default;

		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& rhs) = delete;
		FPSComponent& operator=(FPSComponent&& rhs) = delete;

		void SetTextComponent(const std::shared_ptr<TextComponent>& textComp) { m_wTextComponent = textComp; }
	private:
		std::weak_ptr<TextComponent> m_wTextComponent{};
		int m_FramesCounted{};
		float m_Interval{};
	};
	
}
