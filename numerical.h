#ifndef NUMERICAL_ANALYSIS      
#define NUMERICAL_ANALYSIS      //This header file contains numerical algorithms

#include <vector>

int binomial(int n, int k);      //Return binomial coefficient

int bell_number(int n);      //Return number of partitions of a set
                          
double horner(double x, std::vector<double> coe);     //Solve polynomial equations faster than the usual way
                                  
double horner_derivative(double x, std::vector<double> coe);  // Can only be used on polynomials

double bisection(double (*fn)(double), double a, double b, double error_limit, int n);

double golden_search(double (*fn)(double), double a, double c, double error_limit = 0.0001, int n = 1000);










































































#endif
