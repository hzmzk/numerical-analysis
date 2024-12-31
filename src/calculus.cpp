#include "calculus.h"
#include <limits>
#include <cmath>
#include <vector>
#include <iostream>

namespace derivative
{
	double finite_difference(double (*fn)(double), double x1)
	{
		// Not optimal but good enough
		// 
		// Optimal h for finite difference:
		// (fn computation error) ^ 1/2  * (fn / fn'') ^ 1/2
		// 
		// Optimal h for central difference:
		// (fn computation error) ^ 1/3  * (fn / fn''') ^ 1/3

		volatile double x2{ x1 + std::sqrt(std::numeric_limits<double>::epsilon()) * x1 };
		double dx{ x2 - x1 };

		return (fn(x2) - fn(x1)) / dx;
	}

}

namespace integral
{
	double trapezoid(double (*fn)(double), double a, double b, int n)
	{
		// This function uses the trapezoid rule to
		// approximate integral 

		double trapezoid_estimate{ 0.5 * fn(a) + 0.5 * fn(b - a) };

		for (int i{ 1 }; i < n; ++i)
		{
			trapezoid_estimate += fn(a + i * (b - a) / n);
		}

		return trapezoid_estimate * (b - a) / n;
	}
}
