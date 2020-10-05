#include "filereader.h"

// noch einfügen , ShapeSet& s, LightSet& l
bool Scene::fromFile(const std::string& path) {

	std::ifstream file_(path);
	if (!file_.is_open()) {
		std::cerr << "Params file not found!" << std::endl;
		return false;
	}

	std::string line_;
	int i = 0;
	while (getline(file_, line_)) {
		if (line_[0] == '#') continue;
		if (line_.empty()) continue;

		std::stringstream input(line_);
		std::string paramName;

		input >> paramName;
		// read scene
		if (paramName == "Sphere") {

			float px, py, pz, radius, r, g, b, ambient, diffuse, specular, shinyness, refraction;
			input >> px >> py >> pz >> radius >> r >> g >> b >> ambient >> diffuse >> specular >> shinyness >> refraction;

			Color temp(r, g, b);
			Material tempMat(temp, ambient, diffuse, specular, shinyness, refraction);

			Sphere* s = new Sphere(Point(px, py, pz), radius, tempMat);
			S.addShape(s);

			std::cout << "Sphere added" << std::endl;
		}
		else if (paramName == "Plane") {

			float px, py, pz, nx, ny, nz, r, g, b, ambient, diffuse, specular, shinyness, refraction;
			input >> px >> py >> pz >> nx >> ny >> nz >> r >> g >> b >> ambient >> diffuse >> specular >> shinyness >> refraction;

			Color temp(r, g, b);
			Material tempMat(temp, ambient, diffuse, specular, shinyness, refraction);

			Plane* p = new Plane(Point(px, py, pz), Vector3(nx, ny, nz), tempMat);
			S.addShape(p);

			std::cout << "Plane added" << std::endl;

		}
		else if (paramName == "Checkboard") {

		}
		else if (paramName == "Light") {

		}
		else {
			std::cerr << "Unrecognized input: " << paramName << std::endl;
		}
	}

	file_.close();
	return true;
}
