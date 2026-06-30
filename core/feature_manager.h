#pragma once

class FeatureManager : public IEventListener {
public:
	void OnEvent(EventType event) override;
	void UpdateAll();

private:
	EscFeature escFeature;
	TriggerBot triggerBot;
	AimBot aimBot;
	Esp esp;

	bool noRecoilEnabled = false;
};