#pragma once

#include"pch.h"
#include"Object.h"

namespace SerenEngine {
	template<typename To, typename From>
	FORCE_INLINE To StaticCast(From from) { return (To)from; }

	template<typename T>
	T* DownCast(Object* obj) {
		if (obj && obj->IsDerivedFrom(T::RunTimeType)) {
			return (T*)obj;
		}

		return nullptr;
	}

	template<typename T>
	const T* DownCast(const Object* obj) {
		if (obj && obj->IsDerivedFrom(T::RunTimeType)) {
			return (const T*)obj;
		}

		return nullptr;
	}
}