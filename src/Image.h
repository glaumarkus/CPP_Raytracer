#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include "Color.h"
#include <string>
#include <vector>

struct Image {
	int width, height;
	std::vector<Color> imageData;

	Image(int width, int height);
	virtual ~Image();

	int getWidth();
	int getHeight();

	void saveImage();

};


#endif // !IMAGE_H
