#include "numerical.h"
#include <vector>
#include <cmath>
#include <cassert>

int binomial(int n, int k)      //Return binomial coefficient
{
    assert(k >= 0 && n >= k);

    if (n == k || k == 0)
        return 1;

    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}


int bell_number(int n)      //Return number of partitions of a set
{
    assert(n >= 0);

    if (n == 0)
        return 1;

    int sum = 0;

    for (int k = 0; k < n; ++k)
        sum += binomial(n - 1, k) * bell_number(k);
    
    return sum;
}

double horner(double x, std::vector<double> coe)     // Solve polynomial equations faster than the normal way
{
    if (coe.size() == 1)
        return coe[0];

    double lst_coe{ coe[coe.size() - 1] };
    coe.resize(coe.size() - 1);

    return x * horner(x, coe) + lst_coe;
}
                                 
double horner_derivative(double x, std::vector<double> coe)      // Can only be used on polynomials
{
    if (coe.size() == 1)
        return 0;

    if (coe.size() == 2)
        return coe[0];

    coe.resize(coe.size() - 1);

    return x * horner_derivative(x, coe) + horner(x, coe);
}

double bisection(double (*fn)(double), double a, double b, double error_limit = 0.0001, int n = 1000)
{
    assert(a < b);
    assert(fn(a) * fn(b) <= 0);

    if (fn(a) == 0) return a;
    if (fn(b) == 0) return b;

    while (fn(a) * fn(b) < 0) ++a;
    if (fn(a) == 0) return a;

    b = a;
    --a;

    double mid = (a + b) / 2;

    while (n != 0)
    {
        if (fn(mid) == 0) return mid;

        if (fn(mid) * fn(a) < 0) b = mid;
        else if (fn(mid) * fn(b) < 0) a = mid;

        // Stopping criteria
        if (std::abs((mid - (a + b) / 2)) < std::abs(mid) * error_limit)
            return mid;

        mid = (a + b) / 2;
        --n;
    }
    return mid;
}

double golden_search(double (*fn)(double), double a, double c, double error_limit, int n)
{
    assert(a < c);

    double b{ (c + 1.618 * a) / (1 + 1.618) };
    double d{ a - b + c };

    assert(fn(b) < fn(a) && fn(b) < fn(c));

    while (n != 0)
    {
        if (b < d)
        {
            if (fn(d) < fn(b)) a = b;
            else if (fn(d) > fn(b)) c = d;
            else
            {
                if (fn(a) > fn(c)) a = b;
                else c = d;
            }
        }

        else
        {
            if (fn(d) < fn(b)) c = b;
            else if (fn(d) > fn(b)) a = d;
            else
            {
                if (fn(a) > fn(c)) a = d;
                else c = b;
            }
        }

        b = (c + 1.618 * a) / (1 + 1.618);

        // Stopping criteria
        if (std::abs((d - (a - b + c))) < std::abs(d) * error_limit) return d;

        d = a - b + c;
        --n;
    }

    return d;
}