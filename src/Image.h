#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <algorithm>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Color.h"

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


#endif // !IMAGE_H
