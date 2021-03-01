#pragma once

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