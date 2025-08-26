#pragma once
#include "Event.h"
#include "Core/Singleton.h"
#include "Observer.h"
#include <map>
#include <list>


namespace whermst {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t& id, IObserver& observer);
		void RemoveObserver(IObserver& observer);
		void Notify(const Event& event);
	private:
		std::map<Event::id_t, std::list<IObserver*>> _observers;
	};
}