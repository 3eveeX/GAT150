#include "EnginePCH.h"
#include "EventManager.h"
#include "Core/StringHelper.h"

void whermst::EventManager::AddObserver(const Event::id_t& id, IObserver& observer)
{

	_observers[tolower(id)].push_back(&observer);
}

void whermst::EventManager::RemoveObserver(IObserver& observer)
{
	IObserver* observerPtr = &observer;

	for (auto& eventType : _observers) {
		auto& observers = eventType.second;
		// Remove all instances of the observer from the list
		std::erase_if(observers, [observerPtr](auto& observer) { return observer == observerPtr; });
	}
}

void whermst::EventManager::Notify(const Event& event)
{
	/*auto& observers = _observers[tolower(event.GetID())];
	for (auto observer : observers) {
		observer->OnNotify(event);
	}*/
}
