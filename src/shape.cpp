#include "shape.h"

/*
Shape
*/

// Destructor
Shape::~Shape() {}

// generic
bool Shape::getShadow(Intersection& i, Shape* s, const float& ref_t) {
	if (s->intersect(i)) 
		if (i.t < ref_t) 
			return true;
	return false;
}
Color Shape::getColor(const Intersection& i, Shape* s, LightSet* l, int rec) {

	// pt and pov for light calculation
	const Point pt = i.ray.calculate(i.t);
	const Vector3 pov = i.ray.direction;

	// ask for shape specific variables
	Vector3 commonNormal;
	getNormal(pt, commonNormal);
	Material localMat;
	getBaseMat(localMat, pt);

	// init of all colors
	Color finColor;
	Color reflectColor = Color();
	Color ambientFinal = Color();
	Color diffuseFinal = Color();
	Color specularFinal = Color();

	const int numLights = l->lights.size();
	for (std::list<Light*>::iterator it = l->lights.begin(); it != l->lights.end(); ++it) {

		Light* curLight = *it;
		Point lightCenter(curLight->position);
		Vector3 lightVector = (lightCenter - pt).normalized();

		Color effectiveColor = localMat.color * curLight->intensity;
		Color ambientColor = effectiveColor * localMat.ambient;
		Color diffuseColor = Color();
		Color specularColor = Color();

		float lDotN = dot(lightVector, commonNormal);

		Ray lightRay(pt, lightVector);
		Intersection lightTest(lightRay);
		curLight->intersect(lightTest);

		Ray shadeRay(pt, lightVector);
		Intersection shadeTest(shadeRay);

		if (!getShadow(shadeTest, s, lightTest.t)) {

			if (lDotN >= 0) {
				diffuseColor = effectiveColor * localMat.diffuse * lDotN;
				Vector3 reflection = reflect((lightVector * -1), commonNormal);
				float rDotE = dot(reflection, pov);
				if (rDotE < 0) {
					float factor = std::pow(rDotE, localMat.shinyness);
					specularColor = curLight->color * localMat.specular * factor;
				}
			}
		}
		finColor += (ambientColor + diffuseColor + specularColor) * localMat.color;
	}
	finColor = finColor * (1.f / numLights);
	

	if (localMat.refraction > 0.1 && rec > 0) {
		Vector3 reflectVec = reflect(pov, commonNormal);
		Ray reflectRay(pt, reflectVec);
		Intersection reflectI(reflectRay);
		if (s->intersect(reflectI)) {
			reflectColor = i.pShape->getColor(reflectI, s, l, --rec);
		}
		finColor = finColor * (1.f - localMat.refraction) + reflectColor * localMat.refraction;
	}
	return finColor;
}


/*
Plane
*/
// Constructor default
Plane::Plane() {}
// Constructor
Plane::Plane(const Point& position, const Vector3& normal, const Material& mat) :
	position(position),
	normal(normal),
	mat(mat)
{}
// Destructor
Plane::~Plane() {}
// specific
bool Plane::intersect(Intersection& i) {

	bool doesIntersect = false;

	float dDotN = dot(i.ray.direction, normal);
	if (dDotN == 0.0)
		return false;
	float t = dot(position - i.ray.origin, normal) / dDotN;
	if (t <= RAY_T_MIN || t >= i.t)
		return false;

	i.t = t;
	i.pShape = this;
	i.color = mat.color;
	// replace color later
	return true;
}
void Plane::getNormal(const Point& pt, Vector3& norm) {
	norm = normal;
}
void Plane::getBaseMat(Material& m, const Point& pt) {
	m = mat;
}


/*
Rect
*/
// Constructor
Rect::Rect(const Point& origin, const Material& tempMat, Vector3& uCorner, Vector3& vCorner, const std::string& texturePath) :
	uCorner(uCorner),
	vCorner(vCorner)
{

	float sum_x = uCorner.x + vCorner.x + origin.x;
	float sum_y = uCorner.y + vCorner.y + origin.y;
	float sum_z = uCorner.z + vCorner.z + origin.z;


	xMin = std::min(origin.x, sum_x);
	xMax = std::max(origin.x, sum_x);

	yMin = std::min(origin.y, sum_y);
	yMax = std::max(origin.y, sum_y);

	zMin = std::min(origin.z, sum_z);
	zMax = std::max(origin.z, sum_z);

	uNormal = uCorner;
	uMax = uNormal.length();
	uNormal.normalize();
	vNormal = vCorner;
	vMax = vNormal.length();
	vNormal.normalize();

	normal = cross(uNormal, vNormal);

	position = origin;
	mat = tempMat;

	// if texture given, load 
	if (texturePath.size() != 0) {
		hasTexture = true;
		t.readTexture(texturePath);
		std::cout << "added Texture" << std::endl;
	}

	// Debug

	/*

	std::cout << "Origin" << std::endl;
	position.print();

	std::cout << "Normal" << std::endl;
	normal.print();

	std::cout << "u" << std::endl;
	uNormal.print();

	std::cout << "v" << std::endl;
	vNormal.print();

	std::cout << uMax <<" " <<vMax << std::endl;

	std::cout << "x between" << xMin << " " << xMax <<std::endl;
	std::cout << "y between" << yMin << " " << yMax << std::endl;
	std::cout << "z between" << zMin << " " << zMax << std::endl;


	*/

}
// Destructor
Rect::~Rect() {}
// specific
bool Rect::intersect(Intersection& i) {

	bool doesIntersect = false;
	i.ray.direction.print();
	normal.print();

	float dDotN = dot(i.ray.direction, normal);
	std::cout << dDotN << std::endl;
	if (dDotN == 0.0)
		return false;
	float t = dot(position - i.ray.origin, normal) / dDotN;
	if (t <= RAY_T_MIN || t >= i.t)
		return false;

	Point pt = Point(i.ray.calculate(t));
	// check if pt is within bounds
	std::cout << "got here" << std::endl;
	if (inBounds(pt)) {
		i.t = t;
		i.pShape = this;
		i.color = mat.color;
		return true;
	}
	return false;
}
bool Rect::inBounds(const Point& pt) {

	//return true;

	if (xMin == xMax) {
		if (pt.y >= yMin && pt.y <= yMax) {
			if (pt.z >= zMin && pt.z <= zMax) {
				return true;
			}
		}
	}
	else if (yMin == yMax) {
		if (pt.x >= xMin && pt.x <= xMax) {
			if (pt.z >= zMin && pt.z <= zMax) {
				return true;
			}
		}
	}
	else if (zMin == zMax) {
		if (pt.x >= xMin && pt.x <= xMax) {
			if (pt.y >= yMin && pt.y <= yMax) {
				return true;
			}
		}
	}
	else {
		if (pt.x >= xMin && pt.x <= xMax) {
			if (pt.y >= yMin && pt.y <= yMax) {
				if (pt.z >= zMin && pt.z <= zMax) {
					return true;
				}
			}
		}
	}
	return false;
}
Vector2 Rect::getCoords(const Point& pt) {
	
	float u = ((pt - position) * uNormal).length() / uMax;
	float v = ((pt - position) * vNormal).length() / vMax;
	return Vector2(u, v);
}
void Rect::getBaseMat(Material& m, const Point& pt) {
	m = mat;
	if (hasTexture) {
		// 1. determine pt between 0 - 1
		Vector2 adjCoords = getCoords(pt);
		// 2. check color of img at that pos
		t.getColor(m.color, adjCoords.u, adjCoords.v);
	}
};

/*
Spheres
*/
// Constructor
Sphere::Sphere(const Point& center, const float radius, const Material& mat) :
	center(center),
	radius(radius),
	mat(mat) {}
// Destructor
Sphere::~Sphere() {}
// specific
bool Sphere::intersect(Intersection& i) {

	Ray localRay = i.ray;
	localRay.origin -= center;

	float a, b, c;
	a = localRay.direction.length2();
	b = 2 * dot(localRay.direction, localRay.origin);
	c = localRay.origin.length2() - squared(radius);

	float discriminant = squared(b) - 4 * a * c;

	if (discriminant < 0.0)
		return false;

	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	if (t1 > RAY_T_MIN && t1 < i.t)
		i.t = t1;
	else if (t2 > RAY_T_MIN && t2 < i.t)
		i.t = t2;
	else
		return false;

	i.pShape = this;
	i.color = mat.color;

	return true;
}
void Sphere::getNormal(const Point& pt, Vector3& norm) {
	norm = (pt - center);
	norm.normalize();
}
void Sphere::getBaseMat(Material& m, const Point& pt) {
	m = mat;
}

/*
ShapeSet
*/
// Constructor
ShapeSet::ShapeSet() {}
// Destructor
ShapeSet::~ShapeSet() {}
// specific
void ShapeSet::addShape(Shape* shape) {
	shapes.emplace_back(shape);
}
// intersection with all obj
bool ShapeSet::intersect(Intersection& i) {

	bool doesIntersect = false;
	std::list<Shape*>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); it++) {

		Shape* curShape = *it;
		if (curShape->intersect(i)) {
			std::cout << "Checking Shape" << std::endl;
			doesIntersect = true;
		}
	}
	return doesIntersect;
}

/*
Cuboid
*/
// Constructor
Cuboid::Cuboid(const Point& pt, Vector3& v1, Vector3& v2, Vector3& v3, const Material& tempMat, const std::string& texturePath) {
	// creating 6 Rects

	Rect* r1 = new Rect(pt, tempMat, v1, v2, texturePath);
	Rect* r2 = new Rect(pt, tempMat, v1, v3, texturePath);
	Rect* r3 = new Rect(pt, tempMat, v2, v3, texturePath);

	Point pt2(pt.x, pt.y, pt.z);

	pt2 += v1;
	pt2 += v2;
	pt2 += v3;

	Vector3 v4, v5, v6;

	v4 = v1 * -1;
	v5 = v2 * -1;
	v6 = v3 * -1;

	Rect* r4 = new Rect(pt2, tempMat, v4, v5, texturePath);
	Rect* r5 = new Rect(pt2, tempMat, v4, v6, texturePath);
	Rect* r6 = new Rect(pt2, tempMat, v5, v6, texturePath);

	addShape(r1);
	addShape(r2);
	addShape(r3);
	addShape(r4);
	addShape(r5);
	addShape(r6);

}
// Destructor
Cuboid::~Cuboid() {}


/*
Lights
*/

// Constructor
Light::Light(const Point& position, const Color& color, const float intensity) :
	position(position),
	color(color),
	intensity(intensity)
{}
// Destructor
Light::~Light()
{}
// check for intersection with light
void Light::intersect(Intersection& i) {

	Ray localRay = i.ray;
	localRay.origin -= position;

	float a, b, c;
	a = localRay.direction.length2();
	b = 2 * dot(localRay.direction, localRay.origin);
	c = localRay.origin.length2() - squared(1.0f);

	float discriminant = squared(b) - 4 * a * c;

	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	if (t1 > RAY_T_MIN && t1 < i.t)
		i.t = t1;
	else if (t2 > RAY_T_MIN && t2 < i.t)
		i.t = t2;
}
// Constructor
LightSet::LightSet() {}
// Destructor
LightSet::~LightSet() {}
// add a Light obj
void LightSet::addLight(Light* light) {
	lights.emplace_back(light);
}