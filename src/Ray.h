#ifndef RAY_H
#define RAY_H

#include "Vector.h"
#include "Color.h"

static const float RAY_T_MIN = 0.01f;
static const float RAY_T_MAX = 1.0e4f;

struct Ray {
    Point origin;
    Vector3 direction;

    Ray();
    Ray(const Ray& r);
    Ray(const Point& origin, const Vector3& direction);

    virtual ~Ray();
    Point calculate(float t) const;
    Ray& operator =(const Ray& r);
    void print();
};

struct Shape;

struct Intersection {
    Ray ray;
    float t;
    Shape* pShape;
    Color color;

    Intersection();
    Intersection(const Intersection& i);
    Intersection(const Ray& ray);

    virtual ~Intersection();

};


#endif