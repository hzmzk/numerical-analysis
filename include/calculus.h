#ifndef CALCULUS
#define CALCULUS

namespace derivative 
{
	double finite_difference(double (*fn)(double), double x1);
}

namespace integral
{
	double trapezoid(double (*fn)(double), double a, double b, int n = 1000);
}

#endif
