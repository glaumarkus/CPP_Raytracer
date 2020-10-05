#include "Image.h"

Image::Image(int width, int height) :
	width(width),
	height(height)
{
	image = cv::Mat::zeros(height, width, CV_32FC3);
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
	float red = clamp_quick(c.r * 255);
	float blue = clamp_quick(c.b * 255);
	float green = clamp_quick(c.g * 255);
	image.at<cv::Vec3f>(x, y) = cv::Vec3f(blue, green, red);
}


bool Image::saveImage(const std::string& filename) {

	// apply blur to soften edges
	cv::Mat blur;
	cv::GaussianBlur(image, blur, cv::Size(5, 5), 0);

	if (cv::imwrite(filename, blur))
		return true;
	return false;
}

Image::~Image() {}
