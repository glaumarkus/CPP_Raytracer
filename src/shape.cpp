#include "shape.h"


Shape::~Shape(){}

ShapeSet::ShapeSet()
{}

ShapeSet::~ShapeSet()
{}

void ShapeSet::addShape(Shape* shape) {
	shapes.emplace_back(shape);
}

Color ShapeSet::getColor(const Intersection& i,  Shape* s, LightSet* l) {
	return Color();
}


bool Sphere::isShade(Intersection& i, Shape* s, Light* l) {

	bool isShade = false;
	if (s->intersect(i)) {
		isShade = true;
	}
	return isShade;
}

Color Sphere::getColor(const Intersection& i,  Shape* s, LightSet* l) {

	Color finColor;
	const Point pt = i.ray.calculate(i.t);
	const Vector3 pov = i.ray.direction;
	std::list<Light*>::iterator it;

	const int numLights = l->lights.size();
	
	for (it = l->lights.begin(); it != l->lights.end(); ++it) {

		Light* curLight = *it;

		Point lightCenter(curLight->position);
		Vector3 lightVector = (lightCenter - pt).normalized();

		Color effectiveColor = mat.color * curLight->intensity;
		Color ambientColor = effectiveColor * mat.ambient;
		Color diffuseColor = Color();
		Color specularColor = Color();

		Vector3 normal = getNormalFromPt(pt);
		float lDotN = dot(lightVector, normal);

		Ray shadeRay(pt, lightVector);
		Intersection shadeTest(shadeRay);

		if (!isShade(shadeTest, s, curLight)) {

			if (lDotN >= 0) {

				diffuseColor = effectiveColor * mat.diffuse * lDotN;
				Vector3 reflection = reflect((lightVector * -1), normal);
				float rDotE = dot(reflection, pov);

				if (rDotE < 0) {
					float factor = std::pow(rDotE, mat.shinyness);
					specularColor = curLight->color * mat.specular * factor;
				}
			}
		}
		finColor += (ambientColor + diffuseColor + specularColor) * mat.color;
	}
	finColor = finColor * (1.f / numLights);
	return finColor;
}

Color Plane::getColor(const Intersection& i,  Shape* s, LightSet* l) {
	return mat.color;
}

Color Checkboard::getColor(const Intersection& i,  Shape* s, LightSet* l) {
	
	Point p = i.ray.calculate(i.t);
	return getBaseColor(p);
}

Color Checkboard::getBaseColor(const Point& p) {

	float x = std::floor(p.x / tilesize);
	float y = std::floor(p.y / tilesize);
	float z = std::floor(p.z / tilesize);

	if ((int)(x + y + z) % 2 != 0)
	{
		return mat.color;
	}
	else {
		return Color();
	}
}


bool ShapeSet::intersect(Intersection& i) {

	bool doesIntersect = false;
	std::list<Shape*>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); it++) {

		Shape *curShape = *it;
		if (curShape->intersect(i)) {
			doesIntersect = true;
		}
	}
	return doesIntersect;
}

Plane::Plane(const Point& position, const Vector3& normal, const Material& mat) : 
	position(position),
	normal(normal),
	mat(mat)
{}

Checkboard::Checkboard(const Point& position, const Vector3& normal, const Material& mat, float tilesize) : 
	position(position),
	normal(normal),
	mat(mat),
	tilesize(tilesize)
{}

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

bool Checkboard::intersect(Intersection& i) {

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

Plane::~Plane(){}
Checkboard::~Checkboard() {}

Sphere::Sphere(const Point& center, const float radius, const Material& mat) :
	center(center),
	radius(radius),
	mat(mat)
{}

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

Vector3 Sphere::getNormalFromPt(const Point& p) {

	Vector3 normal(p - center);
	normal.normalize();
	return normal;
}

Sphere::~Sphere()
{}

Light::Light(const Point& position, const Color& color, const float intensity) : 
	position(position),
	color(color),
	intensity(intensity)
{}

Light::~Light()
{}

LightSet::LightSet(){}

LightSet::~LightSet(){}

void LightSet::addLight(Light* light) {
	lights.emplace_back(light);
}
