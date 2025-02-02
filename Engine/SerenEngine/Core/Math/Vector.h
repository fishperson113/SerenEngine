#pragma once
#include "Ultils.h"

namespace SerenEngine
{
	namespace Math
	{
		class SEREN_API VECTOR2
		{
		private:
			float x;
			float y;
		public:
			VECTOR2(float x = 0, float y = 0) :x(x), y(y){}
			float FORCE_INLINE Magnitude() const;			
			VECTOR2 Normalized() const;
			//float FORCE_INLINE sqrMagnitude() const;
			float& operator[](int index);
			//int Equals(VECTOR2 in) const;
			void Set(float newx, float newy);
			std::string ToString() const;
			float Angle(const VECTOR2& to) const;
			float FORCE_INLINE Dot( const VECTOR2& to) const;
			float FORCE_INLINE Distance(const VECTOR2& to) const;
			VECTOR2 FORCE_INLINE Lerp(const VECTOR2& to, float t);
			VECTOR2 FORCE_INLINE sLerp(const VECTOR2& to, float t);
			VECTOR2 FORCE_INLINE cubic_interpolate(const VECTOR2& p_b, const VECTOR2& p_pre_a, const VECTOR2& p_post_b, float p_weight) const;
			VECTOR2 FORCE_INLINE cubic_interpolate_in_time(const VECTOR2& p_b, const VECTOR2& p_pre_a, const VECTOR2& p_post_b, float p_weight, float p_b_t, float p_pre_a_t, float p_post_b_t) const;
			VECTOR2 FORCE_INLINE bezier_interpolate(const VECTOR2& p_control_1, const VECTOR2& p_control_2, const VECTOR2& p_end, float p_t) const;
			VECTOR2 FORCE_INLINE bezier_derivative(const VECTOR2& p_control_1, const VECTOR2& p_control_2, const VECTOR2& p_end, float p_t) const;
			VECTOR2 FORCE_INLINE direction_to(const VECTOR2& p_to) const;
			void normalize();

			VECTOR2 move_toward(const VECTOR2& p_to, float p_delta) const
			{
				VECTOR2 v = *this;
				VECTOR2 vd = p_to - v;
				float len = vd.Magnitude();
				return len <= p_delta || len < (float)CMP_EPSILON ? p_to : v + vd / len * p_delta;

			}
			/*loat cross(const VECTOR2& p_other) const;
			VECTOR2 posmod(float p_mod) const;
			VECTOR2 posmodv(const VECTOR2& p_modv) const;
			VECTOR2 project(const VECTOR2& p_to) const;
			VECTOR2 plane_project(float p_d, const VECTOR2& p_vec) const;
			VECTOR2 slide(const VECTOR2& p_normal) const;
			VECTOR2 bounce(const VECTOR2& p_normal) const;
			VECTOR2 reflect(const VECTOR2& p_normal) const;

			bool is_equal_approx(const VECTOR2& p_v) const;
			bool is_zero_approx() const;
			bool is_finite() const;*/

			VECTOR2 operator+(const VECTOR2& p_v) const;
			void operator+=(const VECTOR2& p_v);
			VECTOR2 operator-(const VECTOR2& p_v) const;
			void operator-=(const VECTOR2& p_v);
			VECTOR2 operator*(const VECTOR2& p_v1) const;

			VECTOR2 operator*(float p_rvalue) const;
			void operator*=(float p_rvalue);
			void operator*=(const VECTOR2& p_rvalue) { *this = *this * p_rvalue; }

			VECTOR2 operator/(const VECTOR2& p_v1) const;

			VECTOR2 operator/(float p_rvalue) const;

			void operator/=(float p_rvalue);
			void operator/=(const VECTOR2& p_rvalue) { *this = *this / p_rvalue; }

			VECTOR2 operator-() const;

			bool operator==(const VECTOR2& p_vec2) const;
			bool operator!=(const VECTOR2& p_vec2) const;

			bool operator<(const VECTOR2& p_vec2) const { return x == p_vec2.x ? (y < p_vec2.y) : (x < p_vec2.x); }
			bool operator>(const VECTOR2& p_vec2) const { return x == p_vec2.x ? (y > p_vec2.y) : (x > p_vec2.x); }
			bool operator<=(const VECTOR2& p_vec2) const { return x == p_vec2.x ? (y <= p_vec2.y) : (x < p_vec2.x); }
			bool operator>=(const VECTOR2& p_vec2) const { return x == p_vec2.x ? (y >= p_vec2.y) : (x > p_vec2.x); }

			float angle() const;
			static VECTOR2 from_angle(float p_angle);

			VECTOR2 FORCE_INLINE abs() const {
				return VECTOR2(std::abs(x),std:: abs(y));
			}

			VECTOR2 rotated(float p_by) const;
			VECTOR2 orthogonal() const {
				return VECTOR2(y, -x);
			}
			FORCE_INLINE VECTOR2 VECTOR2::operator+(const VECTOR2& p_v) const {
				return VECTOR2(x + p_v.x, y + p_v.y);
			}

			FORCE_INLINE void VECTOR2::operator+=(const VECTOR2& p_v) {
				x += p_v.x;
				y += p_v.y;
			}

			FORCE_INLINE VECTOR2 VECTOR2::operator-(const VECTOR2& p_v) const {
				return VECTOR2(x - p_v.x, y - p_v.y);
			}

			FORCE_INLINE void VECTOR2::operator-=(const VECTOR2& p_v) {
				x -= p_v.x;
				y -= p_v.y;
			}

			FORCE_INLINE VECTOR2 VECTOR2::operator*(const VECTOR2& p_v1) const {
				return VECTOR2(x * p_v1.x, y * p_v1.y);
			}

			FORCE_INLINE VECTOR2 VECTOR2::operator*(float p_rvalue) const {
				return VECTOR2(x * p_rvalue, y * p_rvalue);
			}

			FORCE_INLINE void VECTOR2::operator*=(float p_rvalue) {
				x *= p_rvalue;
				y *= p_rvalue;
			}

			FORCE_INLINE VECTOR2 VECTOR2::operator/(const VECTOR2& p_v1) const {
				return VECTOR2(x / p_v1.x, y / p_v1.y);
			}

			FORCE_INLINE VECTOR2 VECTOR2::operator/(float p_rvalue) const {
				return VECTOR2(x / p_rvalue, y / p_rvalue);
			}

			FORCE_INLINE void VECTOR2::operator/=(float p_rvalue) {
				x /= p_rvalue;
				y /= p_rvalue;
			}

			FORCE_INLINE VECTOR2 VECTOR2::operator-() const {
				return VECTOR2(-x, -y);
			}

			FORCE_INLINE bool VECTOR2::operator==(const VECTOR2& p_vec2) const {
				return x == p_vec2.x && y == p_vec2.y;
			}

			FORCE_INLINE bool VECTOR2::operator!=(const VECTOR2& p_vec2) const {
				return x != p_vec2.x || y != p_vec2.y;
			}
			/*VECTOR2 sign() const;
			VECTOR2 floor() const;
			VECTOR2 ceil() const;
			VECTOR2 round() const;
			VECTOR2 snapped(const VECTOR2& p_by) const;
			VECTOR2 snappedf(float p_by) const;
			VECTOR2 clamp(const VECTOR2& p_min, const VECTOR2& p_max) const;
			VECTOR2 clampf(float p_min, float p_max) const;
			float aspect() const { return x/y; }*/

			//std::string String() const;
			
		};
	}
}