#include "stdio.h"
#include "math.h"
// X = T, F = C(T)

double f(double x)
{
    return ((exp(1) / 3) * x * exp(-x / 3)) - 0.25;
}

double fx(double x)
{
    return (exp(1) / 3) * (exp(-x / 3) - x / 3 * exp(-x / 3));
}

double secant(double x0, double x1, double tol)
{
    double xn_old;
    double xn = x0;
    double xn_new = x1;
    int i = 0;
    do
    {
        xn_old = xn;
        xn = xn_new;
        double df = (f(xn) - f(xn_old));
        if (df == 0.0)
        {
            printf("Error: f'(x) = 0\n");
            return 0.0;
        }
        xn_new = xn - (xn - xn_old) / df * f(xn);
        
        printf("i: %d, xn_new: %f\n", ++i, xn_new);
    } while (fabs(xn_new - xn) > tol);
    return xn_new;
}

double newton(double x0, double tol)
{
    double xn;
    double xn_new = x0;
    int i = 0;
    do
    {
        xn = xn_new;
        double df = fx(xn);
        if (df == 0.0)
        {
            printf("Error: f'(x) = 0\n");
            return 0.0;
        }
        xn_new = xn - f(xn) / df;
        printf("i: %d, xn_new: %f\n", ++i, xn_new);
    } while (fabs(xn_new - xn) > tol);
    return xn_new;
}

int main()
{
    double x0 = 4.0;
    double x1 = 4.1;
    double tol = 1e-6;
    double root = secant(x0, x1, tol);
    printf("Root: %f\n", root);
    return 0;
}