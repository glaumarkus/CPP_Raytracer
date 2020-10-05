#ifndef SHAPE_H
#define SHAPE_H

#include <list>
#include <iostream>
#include <cmath>
#include "Ray.h"
#include "Vector.h"
#include "Material.h"

struct Shape {
	virtual ~Shape();
	virtual bool intersect(Intersection& i) = 0;
};

struct ShapeSet : public Shape {
	std::list<Shape*> shapes;
	ShapeSet();
	virtual ~ShapeSet();
	void addShape(Shape* shape);
	virtual bool intersect(Intersection& i);

};

struct Plane : public Shape {
	Point position;
	Vector3 normal;
	Material mat;

	Plane(const Point& position, const Vector3& normal, const Material& mat);
	virtual ~Plane();

	virtual bool intersect(Intersection& i);
	Color getColor(const Point& p);
};

struct Checkboard : public Shape {
	Point position;
	Vector3 normal;
	Material mat;
	float tilesize;

	Checkboard(const Point& position, const Vector3& normal, const Material& mat, float tilesize);
	virtual ~Checkboard();

	virtual bool intersect(Intersection& i);
	Color getColor(const Point& p);
};

struct Sphere : public Shape {
	Point center;
	float radius;
	Material mat;

	Sphere(const Point& center, const float radius, const Material& mat);
	virtual ~Sphere();

	virtual bool intersect(Intersection& i);
	Color getColor(const Point& p);
};

struct Light {
	Point position;
	Color color;
	float intensity;

	Light(const Point& position, const Color& color, const float intensity);
	virtual ~Light();
};

struct LightSet {
	std::list<Light*> lights;
	LightSet();
	virtual ~LightSet();
	void addLight(Light* light);
};

#endif
