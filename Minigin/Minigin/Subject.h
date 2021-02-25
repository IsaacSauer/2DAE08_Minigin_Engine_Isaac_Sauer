#pragma once
#include <vector>
#include <memory>

namespace dae {
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		Subject() = default;
		
		void AddObserver(const std::weak_ptr<dae::Observer>& observer);

		void RemoveObserver(const std::weak_ptr<dae::Observer>& observer);

	protected:
		void Notify(std::shared_ptr<dae::GameObject> go, int event);
	private:
		std::vector<std::weak_ptr<dae::Observer>> m_Observers{};
	};
}
