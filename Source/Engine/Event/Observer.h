#pragma once
#include "Event.h"

namespace whermst {
	class IObserver {
public:
		virtual ~IObserver() = default;
		virtual void OnNotify(const Event& event) = 0;
	};
}