#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <algorithm>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Color.h"
#include "Vector.h"

struct Image {
	const int width, height;
	cv::Mat image;

	Image(int width, int height);
	virtual ~Image();

	int getWidth();
	int getHeight();

	void changePixel(const Color& c, const int x, const int y);
	bool saveImage(const std::string& filename);

};

struct Texture {
	cv::Mat texture;
	int width, height;

	//Texture();
	void readTexture(const std::string& filename);
	void getColor(Color& c, const float& u, const float& v);
	virtual ~Texture();

};


#endif // !IMAGE_H