#pragma once

namespace TriggerBotSwitch
{
	extern std::atomic<bool> Toggle;
}

class TriggerBot
{
public:
	bool Toggle();
	void SanityCheck();
};