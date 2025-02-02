#include "Ultils.h"
namespace SerenEngine
{
	namespace Math
	{
		float Mathh::snapped(float p_value, float p_step) {
			if (p_step != 0) {
				p_value = Mathh::floor(p_value / p_step + 0.5) * p_step;
			}
			return p_value;
		}
	}
}