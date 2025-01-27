#pragma once

#include "EventContext.h"

namespace SerenEngine
{
	template <typename T> using EventCallback = std::function<bool(const T&)>;
	class SEREN_API IEventAction
	{
	public:
		virtual ~IEventAction() = default;
		virtual bool Execute(const EventContext* context) = 0;
	};
	template <typename T>
	class SEREN_API EventAction : public IEventAction
	{
	public:
		EventAction(const EventCallback<T>& callback) : m_Callback(callback) {}
		virtual bool Execute(const EventContext* context) override
		{
			STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "T must derive from EventContext");
			return m_Callback(*static_cast<const T*>(context));
		}
	private:
		EventCallback<T> m_Callback;
	};
}