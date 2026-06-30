#include"../libs/includes.h"

void FeatureManager::OnEvent(EventType event)
{
	switch (event) {
	case EventType::ToggleEsp:
		EspSwitch::Toggle = !EspSwitch::Toggle;
		break;
	case EventType::ToggleAimbot:
		AimBotSwitch::Toggle = !AimBotSwitch::Toggle;
		break;
	case EventType::ToggleSuperJmp:
		SuperJmpSwitch::toggle = !SuperJmpSwitch::toggle;
		break;
	case EventType::ToggleNoRecoil:
		noRecoilEnabled = !noRecoilEnabled;
		break;
	case EventType::ToggleTriggerBot:
		TriggerBotSwitch::Toggle = !TriggerBotSwitch::Toggle;
		break;
	case EventType::PressEsc:
		escFeature.Toggle();
		break;
	case EventType::Exit:
		Core::exitswitch = true;
		break;
	}
}

//
// called inside the render
void FeatureManager::UpdateAll()
{
	if (TriggerBotSwitch::Toggle)
	{
		triggerBot.SanityCheck();
		triggerBot.Toggle();
	}

	if (AimBotSwitch::Toggle)
		aimBot.Toggle();

	if (EspSwitch::Toggle)
		esp.Toggle();

}