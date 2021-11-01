#include <iostream>
#include <chrono>
#include <string>
#include "image.hpp"
#include "render.hpp"

int main()
{
	int width, height;
	for(;;) 
	{
		std::cout << "Input width, height: ";
		std::cin >> width >> height;
		if (!std::cin)
		{
			std::cout << "Wrong input. Try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		if (std::cin.get() != '\n')
		{
			std::cout << "Wrong input. Try again.\n";
			continue;
		}
		if (width <= 0 || height <= 0) 
		{
			std::cout << "Width and height should be positive integers. Try again\n";
			continue;
		}
		break;
	}
	double re, im;
	for (;;)
	{
		std::cout << "Input real and imaginary part of c: ";
		std::cin >> re >> im;
		if (!std::cin)
		{
			std::cout << "Wrong input. Try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		if (std::cin.get() != '\n')
		{
			std::cout << "Wrong input. Try again.\n";
			continue;
		}
		break;
	}
	int pixels_on_gird;
	for(;;) 
	{
		std::cout << "Input number of pixels on the segment [0, 1]: ";
		std::cin >> pixels_on_gird;
		if (!std::cin)
		{
			std::cout << "Wrong input. Try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		if (std::cin.get() != '\n')
		{
			std::cout << "Wrong input. Try again.\n";
			continue;
		}
		if (pixels_on_gird <= 0) 
		{
			std::cout << "Number of pixels should be positive integer. Try again.\n";
			continue;
		}
		break;
	}
	std::unique_ptr<JuGen::Chromo::ColorerBase> colorer;
	int choice;
	for (;;)
	{
		std::cout << "Choose coloring type:\n\t1. Black and White\n\t2. Rainbow\n";
		std::cin >> choice;
		if (!std::cin)
		{
			std::cout << "Wrong input. Try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		if (std::cin.get() != '\n')
		{
			std::cout << "Wrong input. Try again.\n";
			continue;
		}
		switch (choice)
		{
		case 1:
			colorer = std::make_unique<JuGen::Chromo::BWColorer>();
			break;
		case 2:
			colorer = std::make_unique<JuGen::Chromo::RainbowColorer>();
			break;
		default:
			std::cout << "Wrong input. Please, input '1' or '2'. Try again.\n";
			continue;
		}
		break;
	}
	try
	{
		JuGen::Image img(width, height);
		JuGen::JuliaRender render(re, im, pixels_on_gird, std::move(colorer));
		std::cout << "Rendering...";
		auto start = std::chrono::steady_clock::now();
		render.draw(img);
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double> dur = stop - start;
		std::cout << "Done! Rendring time: " << dur.count() << "\nInput output file name: ";
		std::string filename;
		std::getline(std::cin, filename);
		filename += ".bmp";
		if (!img.save(filename.c_str())) std::cout << "Output file error.\n";
		else std::cout << "Done!\n";
	}
	catch (std::bad_alloc&)
	{
		std::cerr << "Out of memory\n";
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "Fatal error\n";
	}
	return 0;
}




