#pragma once

namespace JuGen
{

class Color
{
private:
	int m_color;
public:
	constexpr Color() : m_color(0) {}
	constexpr Color(int r, int g, int b) : m_color(r << 16 | g << 8 | b) {}
	~Color() = default;

	int to_int() const { return m_color; }
};

namespace Chromo
{

struct ColorerBase
{
	ColorerBase() = default;
	virtual ~ColorerBase() = default;

	virtual Color color_eval(double t) = 0;
};

struct BWColorer : ColorerBase
{
	BWColorer() = default;
	~BWColorer() = default;
	Color color_eval(double t) override;
};

struct RainbowColorer : ColorerBase
{
	RainbowColorer() = default;
	~RainbowColorer() = default;
	Color color_eval(double t) override;
};

} // Chromo

} // JuGen