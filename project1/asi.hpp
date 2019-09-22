#ifndef ASI_HPP
#define ASI_HPP

typedef double (*FunctionPointer)(double);

double ASI(FunctionPointer f, double a, double b, double tol);

double simpsonRule(FunctionPointer f, double a, double b);

#endif