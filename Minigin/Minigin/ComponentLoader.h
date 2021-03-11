#pragma once
#include "Singleton.h"

namespace dae
{
	class ComponentLoader final : public Singleton<ComponentLoader>
	{
	public:
		template <typename T, typename ... Args>
		std::shared_ptr<T> LoadComponent(Args&& ... args);

	private:
		std::mutex m_ComponentLoaderMutex;
	};

	template <typename T, typename ... Args>
	std::shared_ptr<T> ComponentLoader::LoadComponent(Args&& ... args)
	{
		std::lock_guard<std::mutex> guard(m_ComponentLoaderMutex);
		START_MEASUREMENT();

		return std::make_shared<T>(args...);
	}

#define COMPONENTLOADER dae::ComponentLoader::GetInstance()
}
