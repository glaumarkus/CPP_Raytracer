#include <cmath>
#include "Ray.h"
#include <iostream>

// Ray
Ray::Ray () :
	origin(Vector3()),
	direction(Vector3())
{}
	
Ray::Ray (const Ray& r) : 
	origin(r.origin),
	direction(r.direction)
{}

Ray::Ray(const Point& origin, const Vector3& direction) :
	origin(origin),
	direction(direction)
{}

Point Ray::calculate(float t) {
	return origin + direction * t;
}

Ray& Ray::operator =(const Ray& r){
	origin = r.origin;
	direction = r.direction;
	return *this;
}

void Ray::print() {
	std::cout << "Ray origin ";
	origin.print();
	std::cout << "Ray direction ";
	direction.print();
}

Ray::~Ray()
{}

// intersection
Intersection::Intersection() : 
	ray(Ray()),
	t(RAY_T_MAX),
	pShape(NULL)
{}

Intersection::Intersection(const Intersection& i) : 
	ray(i.ray),
	t(i.t),
	pShape(i.pShape)
{}

Intersection::Intersection(const Ray& ray) : 
	ray(ray),
	t(RAY_T_MAX),
	pShape(NULL)
{}

Intersection::~Intersection()
{}

