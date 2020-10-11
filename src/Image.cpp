#include "Image.h"

Image::Image(int width, int height) :
	width(width),
	height(height)
{
	image = cv::Mat::zeros(height, width, CV_8UC3);
}

int Image::getHeight() {
	return height;
}

int Image::getWidth() {
	return width;
}

inline float clamp_quick(const float& f) {
	return std::max(0.0f, std::min(255.0f, f));
}

void Image::changePixel(const Color& c, const int x, const int y) {
	uchar red = (int)clamp_quick(c.r * 255);
	uchar blue = (int)clamp_quick(c.b * 255);
	uchar green = (int)clamp_quick(c.g * 255);
	image.at<cv::Vec3b>(x, y) = cv::Vec3b(blue, green, red);
}


bool Image::saveImage(const std::string& filename) {

	// apply blur to soften edges
	//cv::Mat blur;
	//cv::GaussianBlur(image, blur, cv::Size(3, 3), 0);

	if (cv::imwrite(filename, image))
		return true;
	return false;
}

Image::~Image() {}

//Texture::Texture() {}

void Texture::readTexture(const std::string& filename) {
	texture = cv::imread(filename, cv::IMREAD_COLOR);
	width = texture.cols;
	height = texture.rows;
	std::cout << "Loaded texture " << filename << " with w/h " << width << " " << height << std::endl;
}

void Texture::getColor(Color& c, const float& u, const float& v) {

	int y = (int)(width * u);
	int x = (int)(height * v);

	// avoid out of bounds
	if (y >= width)
		y = width - 1;
	else if (y < 0)
		y = 0.0f;
	else if (x >= height)
		x = height - 1;
	else if (x < 0)
		x = 0.0f;

	//std::cout << "Checking Texture at: " << x << " " << y << std::endl;
	cv::Vec3b colorAtPixel = texture.at<cv::Vec3b>(x, y);
	c.b = (float)(colorAtPixel[0]) / 255; 
	c.g = (float)(colorAtPixel[1]) / 255;
	c.r = (float)(colorAtPixel[2]) / 255;
}

Texture::~Texture() {}