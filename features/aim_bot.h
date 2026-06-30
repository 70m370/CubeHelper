#pragma once

namespace AimBotSwitch
{
	extern std::atomic<bool> Toggle;
}

class AimBot
{
public:
	bool Toggle();
};