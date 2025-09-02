#include "EnginePCH.h"

void whermst::Object::Read(const json::value_t& value)
{
	whermst::json::Read(value, "name", name, false);
	whermst::json::Read(value, "active", active, false);
}
