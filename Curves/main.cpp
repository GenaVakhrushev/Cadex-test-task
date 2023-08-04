#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <list>
#include <random>
#include <omp.h>

//7. Split implementation into a library of curves (.dll or .so) and executable which uses API of this library
#include "CurvesLibrary.h"

using namespace std;

string GetVectorString(Vector3 vector)
{
	return "(" + to_string(vector.x) + "; " + to_string(vector.y) + "; " + to_string(vector.z) + ")";
}

bool CompareRadius(Circle* c1, Circle* c2)
{
	return c1->r < c2->r;
}

int main()
{
	random_device rd;
	mt19937 gen(rd());

	double minValue = 0.1;

	double maxCircleRadius = 75;
	uniform_real_distribution<double> circleRadiusDistribution(minValue, maxCircleRadius);

	double maxEllipceXRadius = 100;
	double maxEllipceYRadius = 50;
	uniform_real_distribution<double> ellipceXRadiusDistribution(minValue, maxEllipceXRadius);
	uniform_real_distribution<double> ellipceYRadiusDistribution(minValue, maxEllipceYRadius);

	double maxHelixRadius = 100;
	double maxHelixStep = 100;
	uniform_real_distribution<double> helixRadiusDistribution(minValue, maxHelixRadius);
	uniform_real_distribution<double> helixStepDistribution(minValue, maxHelixStep);

	//2. Populate a container (e.g. vector or list) of objects of these types created in random manner with random parameters.
	list<Curve*> curves;
	
	int curvesCount = 10;
	uniform_int_distribution<int> typeDistribution(0, 2);

	for (int i = 0; i < curvesCount; i++)
	{
		int type = typeDistribution(gen);

		switch (type)
		{
		case 0:
			curves.push_back(new Circle(circleRadiusDistribution(gen)));
			break;
		case 1:
			curves.push_back(new Ellipse(ellipceXRadiusDistribution(gen), ellipceYRadiusDistribution(gen)));
			break;
		case 2:
			curves.push_back(new Helix3D(helixRadiusDistribution(gen), helixStepDistribution(gen)));
			break;
		}
	}

	//3. Print coordinates of points and derivatives of all curves in the container at t=PI/4.
	double t = M_PI / 4;
	int i = 0;
	for(Curve* curve : curves)
	{
		Vector3 point = curve->GetPoint(t);
		Vector3 firstDerivative = curve->GetFirstDerivative(t);

		cout << i << ". Point: " << setw(35) << left << GetVectorString(point)  << " FirstDerivative: " << GetVectorString(firstDerivative) << endl;
		i++;
	}

	cout << endl;

	//4. Populate a second container that would contain only circles from the first container
	list<Circle*> circles;

	i = 0;
	for (Curve* curve : curves)
	{
		Circle* circle = dynamic_cast<Circle*>(curve);
		if (circle != nullptr)
		{
			cout << "Add circle from curves at index " << i << endl;
			circles.push_back(circle);
		}
		i++;
	}

	cout << endl;
	
	//5. Sort the second container in the ascending order of circles’ radii.
	circles.sort(CompareRadius);

	cout << "Sort circles by in the ascending order of radius" << endl;

	i = 0;
	for (Circle* circle : circles)
	{
		cout << i << ". Radius = " << circle->r << endl;
		i++;
	}

	cout << endl;

	//6. Compute the total sum of radii of all curves in the second container.
	double radiusSum = 0;

	//8. Implement computation of the total sum of radii using parallel computations (OpenMP uesd)
	omp_set_num_threads(4);

#pragma omp parallel for
	for (Circle* circle : circles)
	{
#pragma omp atomic
		radiusSum += circle->r;
	}

	cout << "Total radius sum = " << radiusSum << endl;
}