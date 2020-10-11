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

			//std::cout << "Sphere added" << std::endl;
		}
		else if (paramName == "Plane") {

			float px, py, pz, nx, ny, nz, r, g, b, ambient, diffuse, specular, shinyness, refraction;
			input >> px >> py >> pz >> nx >> ny >> nz >> r >> g >> b >> ambient >> diffuse >> specular >> shinyness >> refraction;

			Color temp(r, g, b);
			Material tempMat(temp, ambient, diffuse, specular, shinyness, refraction);

			Plane* p = new Plane(Point(px, py, pz), Vector3(nx, ny, nz), tempMat);
			S.addShape(p);
		}
		else if (paramName == "Light") {

			float px, py, pz, r, g, b, i;
			input >> px >> py >> pz >> r >> g >> b >> i;

			Color temp(r, g, b);

			Light* l = new Light(Point(px, py, pz), temp, i);
			L.addLight(l);

			//std::cout << "Light added" << std::endl;

		}
		else if (paramName == "Rect") {

			float px, py, pz, ux, uy, uz, vx, vy, vz, r, g, b, ambient, diffuse, specular, shinyness, refraction;
			std::string texturePath;
			input >> px >> py >> pz >> ux >> uy >> uz >> vx >> vy >> vz >> r >> g >> b >> ambient >> diffuse >> specular >> shinyness >> refraction >> texturePath;

			Color temp(r, g, b);
			Material tempMat(temp, ambient, diffuse, specular, shinyness, refraction);

			Vector3 uCorner = Vector3(ux, uy, uz);
			Vector3 vCorner = Vector3(vx, vy, vz);

			Rect* rect = new Rect(Point(px, py, pz), tempMat, uCorner, vCorner, texturePath);

			S.addShape(rect);
			std::cout << "Rect added" << std::endl;
		}
		else if (paramName == "Cuboid") {

			float px, py, pz, x1, y1, z1, x2, y2, z2, x3, y3, z3, r, g, b, ambient, diffuse, specular, shinyness, refraction;
			std::string texturePath;
			input >> px >> py >> pz >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> r >> g >> b >> ambient >> diffuse >> specular >> shinyness >> refraction >> texturePath;

			Color temp(r, g, b);
			Material tempMat(temp, ambient, diffuse, specular, shinyness, refraction);

			Vector3 v1 = Vector3(x1, y1, z1);
			Vector3 v2 = Vector3(x2, y2, z2);
			Vector3 v3 = Vector3(x3, y3, z3);

			Cuboid* cuboid = new Cuboid(Point(px, py, pz), v1, v2, v3, tempMat, texturePath);

			std::list<Shape*>::iterator it;
			S.addShape(cuboid);
			std::cout << "Cuboid added" << std::endl;
		}
		else {
			std::cerr << "Unrecognized input: " << paramName << std::endl;
		}
	}

	file_.close();
	return true;
}