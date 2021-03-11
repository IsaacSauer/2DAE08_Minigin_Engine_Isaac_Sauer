#pragma once
#include <vector>
#include <memory>
#include "Observer.h"

//Idea: https://gameprogrammingpatterns.com/observer.html
//For Components inheriting from "MonoBehavior"(Use double inheritance) :
//	Inheriting publicly from "Subject" makes the class Observable.
//	Inheriting publicly from "Observer" makes the class an Observer.
//
//	You can add observers to Subject classes using the public function "AddObserver" or remove them using "RemoveObserver"
//	(Currently only possible when having a shared_ptr of the observer).
//	--------------------------
//	Changed the way information is broadcasted,
//	Make a child class of "class EventAttributes" and fill in your required information.
//	--------------------------
//	In your Subject : Notify your "AttributesComponent" using
//	Notify(PARENT->shared_from_this(), "attributesObject");
//--------------------------
//In your Observer : Override the OnNotify method
//dynamic_pointer_cast the EventAttribute to your desired Inherited Attribute Type.
//if the cast is valid : ->Handle the information to your needs

namespace dae {

	template <typename T>
	class Subject
	{
	public:
		Subject() = default;

		void AddObserver(const std::weak_ptr<T>& observer);
		void RemoveObserver(const std::weak_ptr<T>& observer);

		const std::vector<std::weak_ptr<T>>& GetObservers() const;
	private:
		std::vector<std::weak_ptr<T>> m_Observers{};
	};

	template <typename T>
	void Subject<T>::AddObserver(const std::weak_ptr<T>& observer)
	{
		if (std::find_if(m_Observers.begin(), m_Observers.end(),
			[&observer](const std::weak_ptr<T>& A)
			{
				return !A.owner_before(observer) && !observer.owner_before(A);
			}) == m_Observers.end())
		{
			m_Observers.push_back(observer);
		}
	}

	template <typename T>
	void Subject<T>::RemoveObserver(const std::weak_ptr<T>& observer)
	{
		auto result = std::find_if(m_Observers.begin(), m_Observers.end(),
			[&observer](const std::weak_ptr<T>& A)
			{
				return !A.owner_before(observer) && !observer.owner_before(A);
			});
		if (result != m_Observers.end())
		{
			m_Observers.erase(result);
		}
	}

	template <typename T>
	const std::vector<std::weak_ptr<T>>& Subject<T>::GetObservers() const
	{
		return m_Observers;
	}
}
