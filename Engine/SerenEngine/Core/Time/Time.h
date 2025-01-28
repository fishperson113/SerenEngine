#pragma once
#include"pch.h"
namespace SerenEngine {
	class SEREN_API Time {
	public:
		Time() = default;
		Time(float deltaTime) : mDeltaTime(deltaTime), mTimeScale(1.0f) {
		}
		~Time() = default;
		FORCE_INLINE float GetDeltaTime() const { return mDeltaTime; }
		FORCE_INLINE void SetDeltaTime(float value) { mDeltaTime = value; }
		FORCE_INLINE float GetTimeScale() const { return mTimeScale; }
		FORCE_INLINE void SetTimeScale(float value) { mTimeScale = value; }
		FORCE_INLINE friend Time& operator+=(Time& t1, const Time& t2) { t1.mDeltaTime += t2.GetDeltaTime(); return t1; }

		FORCE_INLINE friend bool operator>=(const Time& t1, const Time& t2) { return t1.mDeltaTime >= t2.GetDeltaTime(); }
		FORCE_INLINE friend bool operator>(const Time& t1, const Time& t2) { return t1.mDeltaTime > t2.GetDeltaTime(); }

		FORCE_INLINE friend bool operator<=(const Time& t1, const Time& t2) { return t1.mDeltaTime <= t2.GetDeltaTime(); }
		FORCE_INLINE friend bool operator<(const Time& t1, const Time& t2) { return t1.mDeltaTime < t2.GetDeltaTime(); }

		FORCE_INLINE friend Time& operator-=(Time& t1, const Time& t2) { t1.mDeltaTime -= t2.GetDeltaTime(); return t1; }
	private:
		float mDeltaTime, mTimeScale;
	};
}