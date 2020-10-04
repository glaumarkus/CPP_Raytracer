#include "Image.h"

Image::Image(int width, int height) : 
	width(width),
	height(height)
{
	imageData.resize(width * height);
}

int Image::getHeight() {
	return height;
}

int Image::getWidth() {
	return width;
}

void Image::saveImage() {

	std::ofstream out("out.ppm");
	out << "P3\n" << width << ' ' << height << ' ' << "255\n";
	std::vector<Color>::iterator it;

	for (
		it = imageData.begin();
		it != imageData.end();
		++it
		)
	{
		out << 
			(int)it->r << ' ' << 
			(int)it->g << ' ' <<
			(int)it->b << ' ' << '\n';

	}
}

Image::~Image(){}