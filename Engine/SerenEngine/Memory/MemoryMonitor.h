#pragma once
#include"pch.h"
#include"MemoryManager.h"
//TODO implement static memory monitor
namespace SerenEngine {
	class SEREN_API MemoryMonitor {
	public:
		static MemoryMonitor& Get();
	private:
		static MemoryMonitor* sInstance;
	public:
		~MemoryMonitor();
	protected:
		MemoryMonitor();
	public:
		void Add(MemoryManager* memoryUsage);
		void Remove(MemoryManager* memoryUsage);
		void Update();
		void Clear();
		void DectecMemoryLeaks();
	private:
		std::vector<MemoryManager*> mUsages;
	};
}