#ifndef NS      //This header file contains algorithms 
#define NS      //that solve nonlinear functions

#include "recurrence_relation.h"
#include <cassert>
#include <iostream>

double bisection(double (*fn)(double), double a, double b, int n = 100)
{
    assert(a < b); 
    assert(fn(a)*fn(b) <= 0);
    
    if (fn(a) == 0) return a;
    if (fn(b) == 0) return b;

    while(fn(a)*fn(b) < 0) ++a;
    if (fn(a) == 0) return a;

    b = a;
    --a;
    
    double mid = (a+b)/2;

    while(n != 0)
        {   
            if(fn(mid) == 0) return mid;

            if(fn(mid)*fn(a) < 0) b = mid;
            else if(fn(mid)*fn(b) < 0) a = mid;

            mid = (a + b) / 2;
            --n;
        }

    return mid; 
}

double golden_section_search(double (*fn)(double), double a, double c, int n = 100)
{
    assert(a < c);

    double b{(c + 1.618*a)/ (1 + 1.618)};
    double d{a - b + c};

    assert(fn(b) < fn(a) && fn(b) < fn(c));
    
    while(n != 0)
    {
        if(b < d)
        {
            if(fn(d) < fn(b)) a = b;
            else if(fn(d) > fn(b)) c = d;
            else
            {
                if(fn(a) > fn(c)) a = b;
                else c = d;
            }
        }

        else
        {
            if(fn(d) < fn(b)) c = b;
            else if(fn(d) > fn(b)) a = d;
            else
            {
                if(fn(a) > fn(c)) a = d;
                else c = b;
            }
        }
        
        b = (c + 1.618*a)/ (1 + 1.618);
        d = a - b + c;       
        --n;
    }

    return d;
}





#endif
