#pragma once

#include"../libs/includes.h"


//
// [EVENT BUS] what will receive the event from the ui and call the features
//  - thats my controller.

//
//three simple events
enum class EventType {
	ToggleEsp,
	ToggleAimbot,
	ToggleSuperJmp,
	ToggleNoRecoil,
	ToggleTriggerBot,
	PressEsc,
	Exit
};

//event
class IEventListener {
public:
	virtual void OnEvent(EventType event) = 0;
};

class EventBus {
public:
	void Subscribe(IEventListener* listener) {
		listeners.push_back(listener);
	}

	
	void Publish(EventType event) {
		for (auto* l : listeners)
			l->OnEvent(event);
	}

private:
	std::vector<IEventListener*> listeners;
};