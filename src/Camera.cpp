#include "Camera.h"

Camera::Camera(const Point origin, const Vector3 forward, const Vector3 upguide, float fov, float aspectRatio) :
	origin(origin),
	forward(forward)
{
	right = cross(forward, upguide).normalized();
	up = cross(right, forward);

	h = tan(fov);
	w = h * aspectRatio;
}

Ray Camera::getRay(float x, float y) {
	Vector3 direction = forward + x * w * right + y * h * up;
	return Ray(origin, direction.normalized());
}

//Camera::~Camera()
//{}