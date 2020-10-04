#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include "Ray.h"
#include <cmath>

struct Camera {

	Point origin;
	Vector3 forward, right, up;
	float h, w;

	Camera(
		const Point origin,
		const Vector3 forward,
		const Vector3 upguide,
		float fov,
		float aspectRatio);

	//virtual ~Camera();

	Ray getRay(float x, float y);
};

#endif // !CAMERA_H