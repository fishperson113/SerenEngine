#pragma once

#include "EventAction.h"

namespace SerenEngine
{
	using EventActionList = std::vector<IEventAction*>;
	class SEREN_API EventDispatcher
	{
		friend class Application;
	public:
		~EventDispatcher();

		template <typename T>
		void AddEventListener(const EventCallback <T>& callback)
		{
			STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "T must derive from EventContext");
			const char* eventName = typeid(T).name();
			IEventAction* action = new EventAction<T> (callback);
			m_EventMap[eventName].emplace_back(action);
		}

		template <typename T>
		void DispatchEvent(const T& eventContext)
		{
			STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Dispatch invalid event context");
			const char* eventType = typeid(T).name();
			ASSERT(m_EventMap.find(eventType) != m_EventMap.end() && "Unknow event type");
			for (auto eventAction : m_EventMap.at(eventType)) {
				if (eventAction->Execute(&eventContext)) {
					break;
				}
			}
		}
	private:
		EventDispatcher();
	private:
		std::unordered_map<const char*, EventActionList> m_EventMap;
	};
}