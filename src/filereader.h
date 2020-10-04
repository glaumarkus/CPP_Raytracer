#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>

#include "shape.h"

struct Scene {
	
	ShapeSet S;
	LightSet L;

	bool fromFile(const std::string& path);
};

#endif