#pragma once
#include "pch.h"
#include "Math.h"
#include <cMath>
#include <iostream>
#include <string>

#ifndef PI
#define PI 3.14159265358979323846
#define CMP_EPSILON 1e-6f  
#ifdef _MSC_VER  
#define likely(x)   (x)  
#define unlikely(x) (x)  
#else
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif
#endif
namespace SerenEngine
{
	namespace Math
	{
		class Mathh
		{
		public:
			static   float sin(float p_x) { return ::sinf(p_x); }

			static   float cos(float p_x) { return ::cosf(p_x); }

			static   float tan(float p_x) { return ::tanf(p_x); }

			static   float sinh(float p_x) { return ::sinhf(p_x); }

			static   float sinc(float p_x) { return p_x == 0 ? 1 : ::sin(p_x) / p_x; }

			static   float sincn(float p_x) { return sinc(PI * p_x); }

			static   float cosh(float p_x) { return ::coshf(p_x); }

			static   float tanh(float p_x) { return ::tanhf(p_x); }

			static   float asin(float p_x) { return p_x < -1 ? (-PI / 2) : (p_x > 1 ? (PI / 2) : ::asinf(p_x)); }

			static   float acos(float p_x) { return p_x < -1 ? PI : (p_x > 1 ? 0 : ::acosf(p_x)); }

			static   float atan(float p_x) { return ::atanf(p_x); }

			static   float atan2(float p_y, float p_x) { return ::atan2f(p_y, p_x); }

			static   float asinh(float p_x) { return ::asinhf(p_x); }

			static   float acosh(float p_x) { return p_x < 1 ? 0 : ::acoshf(p_x); }

			static   float atanh(float p_x) { return p_x <= -1 ? -INFINITY : (p_x >= 1 ? INFINITY : ::atanhf(p_x)); }

			static   float sqrt(float p_x) { return ::sqrtf(p_x); }

			static   float fmod(float p_x, float p_y) { return ::fmodf(p_x, p_y); }

			static   float modf(float p_x, float* r_y) { return ::modff(p_x, r_y); }

			static   float floor(float p_x) { return ::floorf(p_x); }

			static   float ceil(float p_x) { return ::ceilf(p_x); }

			static   float pow(float p_x, float p_y) { return ::powf(p_x, p_y); }

			static   float log(float p_x) { return ::logf(p_x); }

			static   float log1p(float p_x) { return ::log1pf(p_x); }

			static   float log2(float p_x) { return ::log2f(p_x); }

			static   float exp(float p_x) { return ::expf(p_x); }
			static  float deg_to_rad(float p_y) { return p_y * (float)(PI / 180.0); }

			static  float rad_to_deg(float p_y) { return p_y * (float)(180.0 / PI); }
			static float snapped(float p_value, float p_step);
			static  float floor(float p_x) { return ::floor(p_x); }


			static float lerp(float p_from, float p_to, float p_weight) { return p_from + (p_to - p_from) * p_weight; }
			static  float cubic_interpolate(float p_from, float p_to, float p_pre, float p_post, float p_weight) {
				return 0.5f *
					((p_from * 2.0f) +
						(-p_pre + p_to) * p_weight +
						(2.0f * p_pre - 5.0f * p_from + 4.0f * p_to - p_post) * (p_weight * p_weight) +
						(-p_pre + 3.0f * p_from - 3.0f * p_to + p_post) * (p_weight * p_weight * p_weight));
			}
			static float cubic_interpolate_angle(float p_from, float p_to, float p_pre, float p_post, float p_weight) {
				float from_rot = fmod(p_from, (float)2*PI);

				float pre_diff = fmod(p_pre - from_rot, (float)2*PI);
				float pre_rot = from_rot + fmod(2.0f * pre_diff, (float)2*PI) - pre_diff;

				float to_diff = fmod(p_to - from_rot, (float)2*PI);
				float to_rot = from_rot + fmod(2.0f * to_diff, (float)2*PI) - to_diff;

				float post_diff = fmod(p_post - to_rot, (float)2*PI);
				float post_rot = to_rot + fmod(2.0f * post_diff, (float)2*PI) - post_diff;

				return cubic_interpolate(from_rot, to_rot, pre_rot, post_rot, p_weight);
			}
			static  float cubic_interpolate_in_time(float p_from, float p_to, float p_pre, float p_post, float p_weight,
				float p_to_t, float p_pre_t, float p_post_t) {
				
				float t = Mathh::lerp(0.0f, p_to_t, p_weight);
				float a1 = Mathh::lerp(p_pre, p_from, p_pre_t == 0 ? 0.0f : (t - p_pre_t) / -p_pre_t);
				float a2 = Mathh::lerp(p_from, p_to, p_to_t == 0 ? 0.5f : t / p_to_t);
				float a3 = Mathh::lerp(p_to, p_post, p_post_t - p_to_t == 0 ? 1.0f : (t - p_to_t) / (p_post_t - p_to_t));
				float b1 = Mathh::lerp(a1, a2, p_to_t - p_pre_t == 0 ? 0.0f : (t - p_pre_t) / (p_to_t - p_pre_t));
				float b2 = Mathh::lerp(a2, a3, p_post_t == 0 ? 1.0f : t / p_post_t);
				return Mathh::lerp(b1, b2, p_to_t == 0 ? 0.5f : t / p_to_t);
			}
			static float cubic_interpolate_angle_in_time(float p_from, float p_to, float p_pre, float p_post, float p_weight,
				float p_to_t, float p_pre_t, float p_post_t) {
				float from_rot = fmod(p_from, (float)2*PI);

				float pre_diff = fmod(p_pre - from_rot, (float)2*PI);
				float pre_rot = from_rot + fmod(2.0f * pre_diff, (float)2*PI) - pre_diff;

				float to_diff = fmod(p_to - from_rot, (float)2*PI);
				float to_rot = from_rot + fmod(2.0f * to_diff, (float)2*PI) - to_diff;

				float post_diff = fmod(p_post - to_rot, (float)2*PI);
				float post_rot = to_rot + fmod(2.0f * post_diff, (float)2*PI) - post_diff;

				return cubic_interpolate_in_time(from_rot, to_rot, pre_rot, post_rot, p_weight, p_to_t, p_pre_t, p_post_t);
			}
			static float bezier_interpolate(float p_start, float p_control_1, float p_control_2, float p_end, float p_t) {
				/* Formula from Wikipedia article on Bezier curves. */
				float omt = (1.0f - p_t);
				float omt2 = omt * omt;
				float omt3 = omt2 * omt;
				float t2 = p_t * p_t;
				float t3 = t2 * p_t;

				return p_start * omt3 + p_control_1 * omt2 * p_t * 3.0f + p_control_2 * omt * t2 * 3.0f + p_end * t3;
			}
			static float bezier_derivative(float p_start, float p_control_1, float p_control_2, float p_end, float p_t) {
				/* Formula from Wikipedia article on Bezier curves. */
				float omt = (1.0f - p_t);
				float omt2 = omt * omt;
				float t2 = p_t * p_t;

				float d = (p_control_1 - p_start) * 3.0f * omt2 + (p_control_2 - p_control_1) * 6.0f * omt * p_t + (p_end - p_control_2) * 3.0f * t2;
				return d;
			}
			static float angle_difference(float p_from, float p_to) {
				float difference = fmod(p_to - p_from, (float)2 * PI);
				return fmod(2.0f * difference, (float)2*PI) - difference;
			}

			static   float angle_difference(float p_from, float p_to) {
				float difference = fmod(p_to - p_from, (float)2*PI);
				return fmod(2.0f * difference, (float)2*PI) - difference;
			}
			static   float lerp_angle(float p_from, float p_to, float p_weight) {
				return p_from + Mathh::angle_difference(p_from, p_to) * p_weight;
			}
			static   float inverse_lerp(float p_from, float p_to, float p_value) {
				return (p_value - p_from) / (p_to - p_from);
			}
			static   float remap(float p_value, float p_istart, float p_istop, float p_ostart, float p_ostop) {
				return Mathh::lerp(p_ostart, p_ostop, Mathh::inverse_lerp(p_istart, p_istop, p_value));
			}
			static float CLAMP(float x, float min, float max)
			{
				return std::max(min, std::min(x, max));

			}
			
			static   float smoothstep(float p_from, float p_to, float p_s) {
				if (is_equal_approx(p_from, p_to)) {
					if (likely(p_from <= p_to)) {
						return p_s <= p_from ? 0.0f : 1.0f;
					}
					else {
						return p_s <= p_to ? 1.0f : 0.0f;
					}
				}
				float s = CLAMP((p_s - p_from) / (p_to - p_from), 0.0f, 1.0f);
				return s * s * (3.0f - 2.0f * s);
			}
			static float abs(float g) { return absf(g); }
			static inline int SIGN(float x) {
				return (x > 0) - (x < 0);
			}
			static   float move_toward(float p_from, float p_to, float p_delta) {
				return abs(p_to - p_from) <= p_delta ? p_to : p_from + SIGN(p_to - p_from) * p_delta;
			}
			static   float rotate_toward(float p_from, float p_to, float p_delta) {
				float difference = Mathh::angle_difference(p_from, p_to);
				float abs_difference = Mathh::abs(difference);
				// When `p_delta < 0` move no further than to PI radians away from `p_to` (as PI is the max possible angle distance).
				return p_from + CLAMP(p_delta, abs_difference - (float)PI, abs_difference) * (difference >= 0.0f ? 1.0f : -1.0f);
			}
			static   float linear_to_db(float p_linear) {
				return Mathh::log(p_linear) * (float)8.6858896380650365530225783783321;
			}
			static   float db_to_linear(float p_db) {
				return Mathh::exp(p_db * (float)0.11512925464970228420089957273422);
			}
			static   float round(float p_val) { return ::roundf(p_val); }
			static   int64_t wrapi(int64_t value, int64_t min, int64_t max) {
				int64_t range = max - min;
				return range == 0 ? min : min + ((((value - min) % range) + range) % range);
			}
			static   float wrapf(float value, float min, float max) {
				float range = max - min;
				if (is_zero_approx(range)) {
					return min;
				}
				float result = value - (range * Mathh::floor((value - min) / range));
				if (is_equal_approx(result, max)) {
					return min;
				}
				return result;
			}
			static   float fract(float value) {
				return value - floor(value);
			}
			static  double pingpong(double value, double length) {
				return (length != 0.0) ? abs(fract((value - length) / (length * 2.0)) * length * 2.0 - length) : 0.0;
			}
			
			static  bool is_equal_approx(float a, float b) {
				// Check for exact equality first, required to handle "infinity" values.
				if (a == b) {
					return true;
				}
				// Then check for approximate equality.
				float tolerance = (float)CMP_EPSILON * abs(a);
				if (tolerance < (float)CMP_EPSILON) {
					tolerance = (float)CMP_EPSILON;
				}
				return abs(a - b) < tolerance;
			}

			static  bool is_equal_approx(float a, float b, float tolerance) {
				// Check for exact equality first, required to handle "infinity" values.
				if (a == b) {
					return true;
				}
				// Then check for approximate equality.
				return abs(a - b) < tolerance;
			}
			static  uint32_t halfbits_to_floatbits(uint16_t h) {
				uint16_t h_exp, h_sig;
				uint32_t f_sgn, f_exp, f_sig;

				h_exp = (h & 0x7c00u);
				f_sgn = ((uint32_t)h & 0x8000u) << 16;
				switch (h_exp) {
				case 0x0000u: /* 0 or subnormal */
					h_sig = (h & 0x03ffu);
					/* Signed zero */
					if (h_sig == 0) {
						return f_sgn;
					}
					/* Subnormal */
					h_sig <<= 1;
					while ((h_sig & 0x0400u) == 0) {
						h_sig <<= 1;
						h_exp++;
					}
					f_exp = ((uint32_t)(127 - 15 - h_exp)) << 23;
					f_sig = ((uint32_t)(h_sig & 0x03ffu)) << 13;
					return f_sgn + f_exp + f_sig;
				case 0x7c00u: /* inf or NaN */
					/* All-ones exponent and a copy of the significand */
					return f_sgn + 0x7f800000u + (((uint32_t)(h & 0x03ffu)) << 13);
				default: /* normalized */
					/* Just need to adjust the exponent and shift */
					return f_sgn + (((uint32_t)(h & 0x7fffu) + 0x1c000u) << 13);
				}
			}

			static  float halfptr_to_float(const uint16_t* h) {
				union {
					uint32_t u32;
					float f32;
				} u;

				u.u32 = halfbits_to_floatbits(*h);
				return u.f32;
			}

			static  bool is_zero_approx(float s) {
				return abs(s) < (float)CMP_EPSILON;
			}
			static  float absf(float g) {
				union {
					float f;
					uint32_t i;
				} u;

				u.f = g;
				u.i &= 2147483647u;
				return u.f;
			}
			
			static  uint16_t make_half_float(float f) {
				union {
					float fv;
					uint32_t ui;
				} ci;
				ci.fv = f;

				uint32_t x = ci.ui;
				uint32_t sign = (unsigned short)(x >> 31);
				uint32_t mantissa;
				uint32_t exponent;
				uint16_t hf;

				// get mantissa
				mantissa = x & ((1 << 23) - 1);
				// get exponent bits
				exponent = x & (0xFF << 23);
				if (exponent >= 0x47800000) {
					// check if the original single precision float number is a NaN
					if (mantissa && (exponent == (0xFF << 23))) {
						// we have a single precision NaN
						mantissa = (1 << 23) - 1;
					}
					else {
						// 16-bit half-float representation stores number as Inf
						mantissa = 0;
					}
					hf = (((uint16_t)sign) << 15) | (uint16_t)((0x1F << 10)) |
						(uint16_t)(mantissa >> 13);
				}
				// check if exponent is <= -15
				else if (exponent <= 0x38000000) {
					/*
					// store a denorm half-float value or zero
					exponent = (0x38000000 - exponent) >> 23;
					mantissa >>= (14 + exponent);

					hf = (((uint16_t)sign) << 15) | (uint16_t)(mantissa);
					*/
					hf = 0; //denormals do not work for 3D, convert to zero
				}
				else {
					hf = (((uint16_t)sign) << 15) |
						(uint16_t)((exponent - 0x38000000) >> 13) |
						(uint16_t)(mantissa >> 13);
				}

				return hf;
			}

			static float snap_scalar(float p_offset, float p_step, float p_target) {
				return p_step != 0 ? Mathh::snapped(p_target - p_offset, p_step) + p_offset : p_target;
			}

			static float snap_scalar_separation(float p_offset, float p_step, float p_target, float p_separation) {
				if (p_step != 0) {
					float a = Mathh::snapped(p_target - p_offset, p_step + p_separation) + p_offset;
					float b = a;
					if (p_target >= 0) {
						b -= p_separation;
					}
					else {
						b += p_step;
					}
					return (Mathh::abs(p_target - a) < Mathh::abs(p_target - b)) ? a : b;
				}
				return p_target;
			}
		};
	}
}