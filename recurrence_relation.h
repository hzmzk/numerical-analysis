#ifndef RR      //This header file contains numerical algorithms
#define RR      //that make use of recursion

#include <vector>
#include <cassert>

int binomial(int n, int k)      //Return binomial coefficient
{
    assert(k >= 0 && n >= k);

    if(n == k || k == 0)
        return 1;

    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}


int bell_number(int n)      //Return number of partitions of a set
{
    assert(n >= 0);

    if(n==0)
        return 1;

    int sum = 0;
    
    for(int k = 0; k < n; ++k)
    {
        sum += binomial(n-1, k)*bell_number(k);
    }    
    
    return sum;
}

template <typename T>                           //Solve polynomial equations 
double horner(double x, std::vector<T> coe)     //faster than the usual way
{
    if(coe.size() == 1)
        return coe[0];

    T lst_coe{coe[coe.size()-1]};

    coe.resize(coe.size()-1);

    return x*horner(x, coe) + lst_coe;
}

template <typename T>                                       
double horner_derivative(double x, std::vector<T> coe)      //Return derivative value 

{
    if(coe.size() == 1)
        return 0;

    if(coe.size() == 2)
        return coe[0];

    coe.resize(coe.size()-1);

    return x*horner_derivative(x, coe) + horner(x, coe);
}











































































#endif
