#include "EventDispatcher.h"

namespace SerenEngine
{
	EventDispatcher::EventDispatcher() :m_EventMap()
	{
	}

	EventDispatcher::~EventDispatcher()
	{
		for (auto& pair : m_EventMap)
		{
			for (auto eventAction : pair.second)
			{
				FREE_MEMORY(eventAction);
			}
			pair.second.clear();
		}
		m_EventMap.clear();
	}
}