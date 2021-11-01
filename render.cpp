#include <thread>
#include <vector>
#include <functional>
#include "render.hpp"

namespace JuGen
{

JuliaRender::JuliaRender() : m_re(0), m_im(0), m_pixels_on_gird(2000), m_colorer() {}

JuliaRender::JuliaRender(double re, double im, int pixels_on_gird, std::unique_ptr<Chromo::ColorerBase>&& colorer) :
	m_re(re), m_im(im), m_pixels_on_gird(pixels_on_gird), m_colorer(std::move(colorer)) {}

void JuliaRender::part_draw(Image& img, int start, int stop)
{
	int width = img.width();
	int height = img.height();
	int o_xcoord = width / 2;
	int o_ycoord = height / 2;
	if (!m_colorer) m_colorer = std::make_unique<Chromo::BWColorer>();
	double t;
	double t1, t2, t3;
	double x, y;
	for (int i = start; i < height && i < stop; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			x = 1.0 * (j - o_xcoord) / m_pixels_on_gird;
			y = 1.0 * (i - o_ycoord) / m_pixels_on_gird;
			for (t = 0; t < 1; t += 0.005)
			{
				t1 = x + y;
				t2 = x - y;
				t3 = 2 * x * y;
				if (t1 * t1 - t3 >= 4) break;
				x = t1 * t2 + m_re;
				y = t3 + m_im;
			}
			img.set_pix(i, j, m_colorer->color_eval(t));
		}
	}
}

void JuliaRender::draw(Image& img)
{
	int height = img.height();
	int part_num = std::thread::hardware_concurrency();
	if (part_num == 0) part_num = 2;
	std::vector<std::thread> thread_vec(part_num - 1);
	for (int i = 0; i < part_num - 1; ++i)
	{
		thread_vec[i] = std::thread(std::mem_fn(&JuliaRender::part_draw), this, std::ref(img), i * height / part_num, (i + 1) * height / part_num);
	}
	part_draw(img, (part_num - 1) * height / part_num, height);
	for (auto& t : thread_vec) t.join();
}

} // JuGen