#pragma once

#include "SystemBase.h"

class SystemPosition : public SystemBase
{
public:
	SystemPosition(SystemType type);
	SystemPosition(const SystemPosition&) = delete;
	SystemPosition& operator=(const SystemPosition&) = delete;
	SystemPosition(SystemPosition&&) = delete;
	SystemPosition&& operator=(SystemPosition&&) = delete;




private:

};