#pragma once

#ifdef CURVESLIBRARY_EXPORTS
#define CURVESLIBRARY_API __declspec(dllexport)
#else
#define CURVESLIBRARY_API __declspec(dllimport)
#endif

struct CURVESLIBRARY_API Vector3
{
	double x = 0;
	double y = 0;
	double z = 0;

	Vector3() { x = 0; y = 0; z = 0; }
	Vector3(double x, double y, double z) { this->x = x; this->y = y, this->z = z; }
};

struct CURVESLIBRARY_API Curve
{
	virtual Vector3 GetPoint(double t) = 0;
	virtual Vector3 GetFirstDerivative(double t) = 0;
};

struct CURVESLIBRARY_API Circle : Curve
{
	double r;

	Circle(double r);

	Vector3 GetPoint(double t) override;
	Vector3 GetFirstDerivative(double t) override;
};

struct CURVESLIBRARY_API Ellipse : Curve
{
	double rX;
	double rY;

	Ellipse(double rX, double rY);

	Vector3 GetPoint(double t) override;
	Vector3 GetFirstDerivative(double t) override;
};

struct CURVESLIBRARY_API Helix3D : Curve
{
	double r;
	double step;

	Helix3D(double r, double step);

	Vector3 GetPoint(double t) override;
	Vector3 GetFirstDerivative(double t) override;
};