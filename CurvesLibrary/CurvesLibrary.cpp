#include "pch.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <stdexcept>

#include "CurvesLibrary.h"

using namespace std;

Circle::Circle(double r)
{
	if (r <= 0)
	{
		throw std::invalid_argument("Radius must be positive");
	}

	this->r = r;
}

Vector3 Circle::GetPoint(double t)
{
	Vector3 result;

	result.x = r * cos(t);
	result.y = r * sin(t);
	result.z = 0;

	return result;
}

Vector3 Circle::GetFirstDerivative(double t)
{
	Vector3 result;

	result.x = -r * sin(t);
	result.y = r * cos(t);
	result.z = 0;

	return result;
}

Ellipse::Ellipse(double rX, double rY)
{
	if (rX <= 0)
	{
		throw std::invalid_argument("Radius along X axis must be positive");
	}

	if (rY <= 0)
	{
		throw std::invalid_argument("Radius along Y axis must be positive");
	}

	this->rX = rX;
	this->rY = rY;
}

Vector3 Ellipse::GetPoint(double t)
{
	Vector3 result;

	result.x = rX * cos(t);
	result.y = rY * sin(t);
	result.z = 0;

	return result;
}

Vector3 Ellipse::GetFirstDerivative(double t)
{
	Vector3 result;

	result.x = -rX * sin(t);
	result.y = rY * cos(t);
	result.z = 0;

	return result;
}

Helix3D::Helix3D(double r, double step)
{
	if (r <= 0)
	{
		throw std::invalid_argument("Radius must be positive");
	}

	this->r = r;
	this->step = step;
}

Vector3 Helix3D::GetPoint(double t)
{
	Vector3 result;

	result.x = r * cos(t);
	result.y = r * sin(t);
	result.z = step * t / (2 * M_PI);

	return result;
}

Vector3 Helix3D::GetFirstDerivative(double t)
{
	Vector3 result;

	result.x = -r * sin(t);
	result.y = r * cos(t);
	result.z = step / (2 * M_PI);

	return result;
}
