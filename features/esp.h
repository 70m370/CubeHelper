#pragma once

namespace EspSwitch
{
	extern std::atomic<bool> Toggle;
}

class Esp
{
public:
	void Toggle();
};