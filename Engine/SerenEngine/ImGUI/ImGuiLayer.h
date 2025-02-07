#pragma once
#include "pch.h"
#include "Core/Layer/Layer.h"
#include "Core/Event/EventContext.h"

namespace SerenEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Time deltaTime) override {};
		virtual void OnGuiRender() override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
	public:
		virtual bool OnWindowResizedEvent(const WindowResizedEvent&) override;
	};

}
