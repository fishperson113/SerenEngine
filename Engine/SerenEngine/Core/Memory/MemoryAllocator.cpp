#include "MemoryAllocator.h"
namespace SerenEngine
{
	MemoryAllocator::MemoryAllocator(size_t memorySize, void* address) : mMemorySize(memorySize), mStartAddress(address), mUsedMemory(0), mAllocationCount(0)
	{
	}
	uint8_t MemoryAllocator::GetAddressAdjustment(const void* address, uint8_t alignment)
	{
		ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");
		uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment - 1));
		if (adjustment == alignment) {
			return 0;
		}
		return adjustment;
	}
	bool MemoryAllocator::IsPowerOfTwo(uint8_t alignment)
	{
		return (alignment & (alignment - 1)) == 0;
	}
}