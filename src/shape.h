#ifndef SHAPE_H
#define SHAPE_H

#include <list>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>

#include "Ray.h"
#include "Vector.h"
#include "Material.h"
#include "Color.h"

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

struct Shape {
	virtual ~Shape();
	virtual bool intersect(Intersection& i) = 0;
	virtual Color getColor(const Intersection& i,  Shape* s, LightSet* l) = 0;

};

struct ShapeSet : public Shape {
	std::list<Shape*> shapes;
	ShapeSet();
	virtual ~ShapeSet();
	void addShape(Shape* shape);
	virtual bool intersect(Intersection& i);
	virtual Color getColor(const Intersection& i, Shape* s, LightSet* l);

};

struct Plane : public Shape {
	Point position;
	Vector3 normal;
	Material mat;

	Plane(const Point& position, const Vector3& normal, const Material& mat);
	virtual ~Plane();

	virtual bool intersect(Intersection& i);
	virtual Color getColor(const Intersection& i, Shape* s, LightSet* l);


};

struct Checkboard : public Shape {
	Point position;
	Vector3 normal;
	Material mat;
	float tilesize;

	Checkboard(const Point& position, const Vector3& normal, const Material& mat, float tilesize);
	virtual ~Checkboard();

	virtual bool intersect(Intersection& i);
	virtual Color getColor(const Intersection& i, Shape* s, LightSet* l);
	Color getBaseColor(const Point& p);
};

struct Sphere : public Shape {
	Point center;
	float radius;
	Material mat;

	Sphere(const Point& center, const float radius, const Material& mat);
	virtual ~Sphere();

	virtual bool intersect(Intersection& i);
	virtual Color getColor(const Intersection& i, Shape* s, LightSet* l);
	bool isShade(Intersection& i,Shape* s, Light* l);
	Vector3 getNormalFromPt(const Point& p);
};




#endif
