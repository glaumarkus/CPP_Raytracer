#include "shape.h"

bool Shape::intersect(Intersection& i) {
	return false;
}

Shape::~Shape(){}

ShapeSet::ShapeSet()
{}

ShapeSet::~ShapeSet()
{}

void ShapeSet::addShape(Shape shape) {
	shapes.emplace_back(shape);
}

bool ShapeSet::intersect(Intersection& i) {

	bool doesIntersect = false;
	std::list<Shape>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); it++) {

		Shape curShape = *it;
		if (curShape.intersect(i)) {
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
