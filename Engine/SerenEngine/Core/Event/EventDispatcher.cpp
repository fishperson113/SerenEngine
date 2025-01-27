#include "EventDispatcher.h"

namespace SerenEngine
{
	EventDispatcher::EventDispatcher() : mEventActionMap() {
	}

	EventDispatcher::~EventDispatcher() {
		for (auto& pair : mEventActionMap) {
			for (auto eventAction : pair.second) {
				FREE_MEMORY(eventAction);
			}
			pair.second.clear();
		}
		mEventActionMap.clear();
	}
}