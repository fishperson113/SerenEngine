#pragma once
#include"pch.h"
#include"Core/Type/RTTI.h"
#include"Core/Application.h"
namespace SerenEngine {
	class SEREN_API Renderer {
	public:
		DECLARE_RTTI
	public:
		Renderer();
		~Renderer();
		void OnInit(const ApplicationConfiguration&);
		bool BeginScene();
		void Render();
		void EndScene();
		void OnShutDown();
	};
}