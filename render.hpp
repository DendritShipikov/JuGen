#pragma once

#include <memory>
#include "image.hpp"

namespace JuGen
{

class JuliaRender
{
public:
	double m_re;
	double m_im;
	int m_pixels_on_gird;
	std::unique_ptr<Chromo::ColorerBase> m_colorer;

	void part_draw(Image&, int start, int stop);
public:
	JuliaRender();
	JuliaRender(double re, double im, int pixels_on_gird, std::unique_ptr<Chromo::ColorerBase>&& colorer);
	JuliaRender(const JuliaRender&) = delete;
	JuliaRender& operator=(const JuliaRender&) = delete;
	~JuliaRender() = default;

	void draw(Image&);
};


} // JuGen



