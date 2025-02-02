#include "Vector.h"
namespace SerenEngine
{
	namespace Math
	{
		float VECTOR2::Magnitude() const
		{
			return sqrt(x * x + y * y);
		}
		VECTOR2 VECTOR2::Normalized() const
		{
			float mag = Magnitude();
			if (mag < 1e-6)
			{
				return VECTOR2(0, 0);
			}
			else return VECTOR2(x / mag, y / mag);
		}
		
		float& VECTOR2:: operator[](int index)
		{
			if (index == 0) return x;
			if (index == 1) return y;
			throw std::out_of_range("error");
		}
		void VECTOR2::Set(float newx, float newy)
		{
			x = newx;
			y = newy;
		}
		std::string VECTOR2::ToString() const
		{
			std::string result = "[" + std::to_string(x) + "," + std::to_string(y) + "]";
			return result;
		}
		float VECTOR2::Angle(const VECTOR2& to) const
		{
			return atan2(to.y - y, to.x - x);
		}

		float VECTOR2::Dot( const VECTOR2& to) const
		{
			return x * to.x + y * to.y;
		}
		float VECTOR2::Distance(const VECTOR2& to) const
		{
			return sqrt((to.x - x) * (to.x - x) + (to.y - y) * (to.y - y));
		}
		VECTOR2 VECTOR2::Lerp(const VECTOR2& to, float t)
		{
			return VECTOR2((1 - t) * x + t * to.x), ((1 - t) * y + t * to.y);
		}
		VECTOR2 VECTOR2::sLerp(const VECTOR2& to, float t)
		{
			float start = Magnitude();
			float end = to.Magnitude();
			if (start == 0.0f || end == 0.0f)
			{
				return Lerp(to, t);
			}
			float angle = Angle(to);
			
			float result = Mathh::lerp(start, end, t);
			return rotated(angle * t) * (result / start);
		}
		VECTOR2 VECTOR2::cubic_interpolate(const VECTOR2& p_b, const VECTOR2& p_pre_a, const VECTOR2& p_post_b, float p_weight) const
		{
			VECTOR2 r = *this;
			r.x = Mathh::cubic_interpolate(r.x, p_b.x, p_pre_a.x,p_post_b.x, p_weight);
			r.y = Mathh::cubic_interpolate(r.y, p_b.y, p_pre_a.y, p_post_b.y, p_weight);
			return r;
		}
		float VECTOR2::Angle(const VECTOR2& to) const
		{
			float dot = this->Dot(to);
			float magnitude = Magnitude() * to.Magnitude();
			return magnitude == 0 ? 0 : std::acos(dot / magnitude);
		}
		VECTOR2 VECTOR2::cubic_interpolate_in_time(const VECTOR2& p_b, const VECTOR2& p_pre_a, const VECTOR2& p_post_b, float p_weight, float p_b_t, float p_pre_a_t, float p_post_b_t) const 
		{
			{
				VECTOR2 res = *this;
				res.x = Mathh::cubic_interpolate_in_time(res.x, p_b.x, p_pre_a.x, p_post_b.x, p_weight, p_b_t, p_pre_a_t, p_post_b_t);
				res.y = Mathh::cubic_interpolate_in_time(res.y, p_b.y, p_pre_a.y, p_post_b.y, p_weight, p_b_t, p_pre_a_t, p_post_b_t);
				return res;
			}
		}
		VECTOR2 VECTOR2::bezier_interpolate(const VECTOR2& p_control_1, const VECTOR2& p_control_2, const VECTOR2& p_end, float p_t) const
		{
			VECTOR2 res = *this;
			res.x = Mathh::bezier_interpolate(res.x, p_control_1.x, p_control_2.x, p_end.x, p_t);
			res.y = Mathh::bezier_interpolate(res.y, p_control_1.y, p_control_2.y, p_end.y, p_t);
			return res;
		}
		VECTOR2 VECTOR2::bezier_derivative(const VECTOR2& p_control_1, const VECTOR2& p_control_2, const VECTOR2& p_end, float p_t) const {
			VECTOR2 res = *this;
			res.x = Mathh::bezier_derivative(res.x, p_control_1.x, p_control_2.x, p_end.x, p_t);
			res.y = Mathh::bezier_derivative(res.y, p_control_1.y, p_control_2.y, p_end.y, p_t);
			return res;
		}
		void VECTOR2::normalize() {
			float l = x * x + y * y;
			if (l != 0) {
				l = Mathh::sqrt(l);
				x /= l;
				y /= l;
			}
		}

		VECTOR2 VECTOR2::direction_to(const VECTOR2& p_to) const {
			VECTOR2 ret(p_to.x - x, p_to.y - y);
			ret.normalize();
			return ret;
		}
		float VECTOR2::angle() const {
			return Mathh::atan2(y, x);
		}

		VECTOR2 VECTOR2::from_angle(float p_angle) {
			return VECTOR2(Mathh::cos(p_angle), Mathh::sin(p_angle));
		}
		VECTOR2 VECTOR2::rotated(float p_by) const {
			float sine = Mathh::sin(p_by);
			float cosi = Mathh::cos(p_by);
			return VECTOR2(
				x * cosi - y * sine,
				x * sine + y * cosi);
		}
	}
}