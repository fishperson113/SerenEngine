#pragma once

#include "EventAction.h"

namespace SerenEngine
{
	using EventActionList = std::vector<IEventAction*>;
	using EventID = UUID;

	class SEREN_API EventDispatcher
	{
		friend class Application;
	public:
		~EventDispatcher();

		template <typename T>
		void AddEventListener(const EventCallback<T>& callback) {
			STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Add invalid event context");
			EventID eventID = GetTypeUUID<T>();
			// TODO: Allocate with Memory Management System
			IEventAction* eventAction = new EventAction<T>(callback);
			mEventActionMap[eventID].emplace_back(eventAction);
		}

		template <typename T>
		void DispatchEvent(const T& eventContext)
		{
			STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Dispatch invalid event context");
			EventID eventID = GetTypeUUID<T>();

			if (mEventActionMap.find(eventID) == mEventActionMap.end()) {
				return;
			}

			for (auto eventAction : mEventActionMap.at(eventID)) {
				if (eventAction->Execute(&eventContext)) {
					break;
				}
			}
		}
	private:
		EventDispatcher();
	private:
		std::unordered_map<EventID, EventActionList> mEventActionMap;
	};
}