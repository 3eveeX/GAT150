#pragma once
#include "json.h"

namespace whermst {
	class ISerializable {
	public:
		virtual ~ISerializable() = default;

		virtual void Read(const json::value_t& value) = 0;

	};
}