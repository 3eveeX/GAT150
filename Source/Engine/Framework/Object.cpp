#include "EnginePCH.h"

void whermst::Object::Read(const json::value_t& value)
{
	JSON_READ(value, name);
	JSON_READ(value, active);
}
