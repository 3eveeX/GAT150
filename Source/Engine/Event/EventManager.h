#pragma once
#include "Event.h"
#include "Core/Singleton.h"
#include "Observer.h"
#include <map>
#include <list>

#define OBSERVER_ADD(event_id)				whermst::EventManager::Instance().AddObserver(#event_id, *this)
#define OBSERVER_REMOVE_SELF				whermst::EventManager::Instance().RemoveObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	whermst::EventManager::Instance().Notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				whermst::EventManager::Instance().Notify({ #event_id, true })
namespace whermst {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t& id, IObserver& observer);
		void RemoveObserver(IObserver& observer);
		void Notify(const Event& event);

		void removeAllObservers() { _observers.clear(); }
	private:
		std::map<Event::id_t, std::list<IObserver*>> _observers;
	};
}