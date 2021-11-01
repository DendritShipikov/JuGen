#include "color.hpp"

namespace JuGen
{

namespace Chromo
{

Color BWColorer::color_eval(double t)
{
	int c = static_cast<int>(t * 0xff);
	return Color(c, c, c);
} 

Color RainbowColorer::color_eval(double t)
{
	if (t < 0) return Color(0xff, 0, 0);
	double l = (1 - t) * 0xff;
	int i = static_cast<int>(t * 4);
	t -= i * 0.25;
	int max_val = static_cast<int>(l);
	int mid_val = static_cast<int>(4 * l * t);
	int rmid_val = max_val - mid_val;
	switch (i)
	{
	case 0:
		return Color(max_val, mid_val, 0);
	case 1:
		return Color(rmid_val, max_val, 0);
	case 2:
		return Color(0, max_val, mid_val);
	case 3:
		return Color(0, rmid_val, max_val);
	default:
		return Color();
	}
}

} // Chromo

} // JuGen
