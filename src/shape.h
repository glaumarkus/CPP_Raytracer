#ifndef SHAPE_H
#define SHAPE_H

#include <list>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <algorithm>

#include "Ray.h"
#include "Vector.h"
#include "Material.h"
#include "Color.h"
#include "Image.h"


/*
Lights
*/

struct Light {
	Point position;
	Color color;
	float intensity;

	Light(const Point& position, const Color& color, const float intensity);
	virtual ~Light();

	void intersect(Intersection& i);
};

struct LightSet {
	std::list<Light*> lights;
	LightSet();
	virtual ~LightSet();
	void addLight(Light* light);
};


/*
Shape
*/

struct Shape {

	Material mat = Material();
	virtual ~Shape();

	// generic functions
	bool getShadow(Intersection& i,  Shape* s, const float& ref_t);
	Color getColor(const Intersection& i, Shape* s, LightSet* l, int rec);

	// virtual functions
	virtual bool intersect(Intersection& i) = 0;
	virtual void getNormal(const Point& pt, Vector3& norm) = 0;
	virtual void getBaseMat(Material& m, const Point& pt) = 0;
};



/*
ShapeSet
*/

struct ShapeSet : public Shape {
	std::list<Shape*> shapes;
	ShapeSet();
	virtual ~ShapeSet();
	void addShape(Shape* shape);

	// virtual functions
	bool intersect(Intersection& i);
	void getNormal(const Point& pt, Vector3& norm) {};
	void getBaseMat(Material& m, const Point& pt) {};
};

/*
Plane
*/

struct Plane : public Shape {
	Point position;
	Vector3 normal;
	Material mat;

	Plane();
	Plane(const Point& position, const Vector3& normal, const Material& mat);
	virtual ~Plane();

	// virtual functions
	virtual bool intersect(Intersection& i);
	void getNormal(const Point& pt, Vector3& norm);
	virtual void getBaseMat(Material& m, const Point& pt);
};

/*
Rect
*/

struct Rect : public Plane {

	Vector3 uCorner;
	Vector3 vCorner;

	float xMin, xMax, yMin, yMax, zMin, zMax;
	Vector3 uNormal, vNormal;
	float uMax, vMax;

	bool hasTexture = false;
	Texture t;

	Rect(const Point& origin, const Material& tempMat, Vector3& uCorner, Vector3& vCorner, const std::string& texturePath);
	virtual ~Rect();

	// virtual functions
	virtual bool intersect(Intersection& i);

	// specific functions
	bool inBounds(const Point& pt);
	Vector2 getCoords(const Point& pt);
	void getBaseMat(Material& m, const Point& pt);
};

/*
Cuboid
*/

struct Cuboid : public ShapeSet {
	Cuboid(const Point& pt, Vector3& v1, Vector3& v2, Vector3& v3, const Material& tempMat, const std::string& texturePath);
	virtual ~Cuboid();
};


/*
Sphere
*/

struct Sphere : public Shape {
	Point center;
	float radius;
	Material mat;

	Sphere(const Point& center, const float radius, const Material& mat);
	virtual ~Sphere();

	// new
	virtual bool intersect(Intersection& i);
	virtual void getNormal(const Point& pt, Vector3& norm);
	virtual void getBaseMat(Material& m, const Point& pt);
};

#endif