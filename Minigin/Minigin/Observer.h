#pragma once
#include "InheritEnum.h"

namespace dae {
	class GameObject;

	class Observer
	{
	public:
		virtual void OnNotify(std::shared_ptr<dae::GameObject> go, int event) = 0;
		virtual ~Observer() = default;
	};

}