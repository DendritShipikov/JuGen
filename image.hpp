#pragma once

#include <Windows.h>
#include "color.hpp"

namespace JuGen
{

class Image
{
private:
	int* m_data;
	BITMAPFILEHEADER m_bfh;
	BITMAPINFOHEADER m_bih;
public:
	Image(int width, int height);
	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;
	~Image() { delete[] m_data; }

	bool save(const char* filename) const;

	int width() const { return m_bih.biWidth; }
	int height() const { return m_bih.biHeight; }

	void set_pix(int i, int j, Color c) { m_data[ + i * m_bih.biWidth + j] = c.to_int(); }
};

} // JuGen