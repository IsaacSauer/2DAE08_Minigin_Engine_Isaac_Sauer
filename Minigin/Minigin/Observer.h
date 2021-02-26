#pragma once
#include "InheritEnum.h"

namespace dae {
	class GameObject;
	
	class EventAttributes
	{
	public:
		EventAttributes() = default;
		virtual ~EventAttributes() = default;
	};
	
	class Observer
	{
	public:
		virtual void OnNotify(std::shared_ptr<dae::GameObject> go, std::shared_ptr<EventAttributes> event) = 0;
		virtual ~Observer() = default;
	};

}