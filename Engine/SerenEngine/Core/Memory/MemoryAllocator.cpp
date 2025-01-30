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
	uint8_t MemoryAllocator::GetAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory) {
		ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");
		uint8_t padding = GetAddressAdjustment(address, alignment);
		if (padding < extraMemory) {
			uint8_t remainPadding = extraMemory - padding;
			if ((remainPadding & (alignment - 1)) != 0) {
				padding += alignment * (1 + (remainPadding / alignment));
			}
			else {
				padding += alignment * (remainPadding / alignment);
			}
		}
		return padding;
	}
	size_t MemoryAllocator::AlignForward(size_t memorySize, uint8_t alignment) {
		ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");
		uintptr_t remainder = memorySize & (alignment - 1);
		if (remainder != 0) {
			memorySize += alignment - remainder;
		}
		return memorySize;
	}

	bool MemoryAllocator::IsPowerOfTwo(uint8_t alignment)
	{
		return (alignment & (alignment - 1)) == 0;
	}
}