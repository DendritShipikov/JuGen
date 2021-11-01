#include <fstream>
#include "image.hpp"

namespace JuGen
{

Image::Image(int width, int height) : m_data(new int[width * height]), m_bfh{}, m_bih{}
{
	m_bfh.bfType = 0x4d42;
	m_bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 4 * width * height;
	m_bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	m_bih.biSize = sizeof(m_bih);
	m_bih.biWidth = width;
	m_bih.biHeight = height;
	m_bih.biPlanes = 1;
	m_bih.biBitCount = 32;
	m_bih.biCompression = BI_RGB;
}

bool Image::save(const char* filename) const
{
	std::ofstream fout(filename, std::ios::binary);
	if (!fout) return false;
	fout.write(reinterpret_cast<const char*>(&m_bfh), sizeof(BITMAPFILEHEADER));
	fout.write(reinterpret_cast<const char*>(&m_bih), sizeof(BITMAPINFOHEADER));
	fout.write(reinterpret_cast<const char*>(m_data), m_bfh.bfSize - m_bfh.bfOffBits);
	fout.close();
	return true;
}

} // JuGen