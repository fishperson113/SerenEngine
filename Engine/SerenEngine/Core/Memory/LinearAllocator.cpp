#include "MemoryAllocator.h"
#include"Core/Logger/Logger.h"
namespace SerenEngine
{
	LinearAllocator::LinearAllocator(size_t memorySize, void* address) : MemoryAllocator(memorySize, address) {
	}
	LinearAllocator::~LinearAllocator() {
	}
	void* LinearAllocator::Allocate(size_t memorySize, uint8_t alignment) {
		ASSERT(memorySize > INVALID_MEMORY_SIZE && "Allocate invalid memory size");
		ASSERT(alignment < MAX_ALLOWED_ALIGNMENT && "Invalid alignment");
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		asUintPtrAddress += mUsedMemory;
		uintptr_t adjustment = GetAddressAdjustment(asVoidPtrAddress, alignment);
		if (mUsedMemory + memorySize + adjustment > mMemorySize) {
			CORE_LOG_WARN("LinearAllocator is full, can not allocate for new data with size {0}", memorySize);
			return nullptr;
		}
		asUintPtrAddress += adjustment;
		mUsedMemory += memorySize + adjustment;
		mAllocationCount += 1;
		return asVoidPtrAddress;
	}
	void LinearAllocator::Free(void* memory) {
		ASSERT(false && "LinearAllocator does not support for free address");
	}
	void LinearAllocator::Clear() {
		mUsedMemory = 0;
		mAllocationCount = 0;
	}
}