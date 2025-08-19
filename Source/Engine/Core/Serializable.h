#pragma once
#include "json.h"

namespace whermst {
	class Serializable {
	public:
		virtual ~Serializable() = default;

		virtual void Read(const json::value_t& value) = 0;

	};
}