#include "probability.h"

double normal_cdf(double z)
{
    return pow(2, -1) * std::erf(z / sqrt(2)) + 0.5;
}

double gamma_cdf(double a, double lambda, double x)
{
    x /= lambda;
    double sum{ 0 };
    for (int n{ 0 }; n < 100; ++n)
        sum += std::pow(x, n) / std::tgamma(a + n + 1);

    return sum * std::exp(-x) * std::pow(x, a);
}