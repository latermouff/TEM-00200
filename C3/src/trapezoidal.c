#include "stdio.h"
#include "math.h"

double trapezio(double (*f)(double), double a, double b, int n);
double trapezio_tol(double (*f)(double), double a, double b, double tol);

double f(double x)
{
    return sin(x);
}

int main()
{
    double res = trapezio(f, 0.0, M_PI, 50);
    double res1 = trapezio_tol(f, 0.0, M_PI, 1e-6);
    printf("Result = %.10f\n", res);
    printf("Result = %.10f\n", res1);
    return 0;
}

double trapezio(double (*f)(double), double a, double b, int n)
{
    double dx = (b - a) / (n - 1);
    double dx2 = dx / 2;
    double acc = f(a) + f(b);

    double aux = 0.0;
    for (int i = 1; i < n - 1; i++)
    {
        aux += f(a + i * dx);
    }
    return dx2 * (acc + 2 * aux);
}

double trapezio_tol(double (*f)(double), double a, double b, double tol)
{
    double dx = b - a;
    double I_old = (f(b) + f(a)) * dx / 2.0;
    double I;
    for (int l = 1; l <= 30; l++)
    {
        int np = 1 << (l - 1);
        double a0 = a + dx / (1 << l);
        double dy = dx / (1 << (l - 1));
        double acc = 0;
        for (int i = 0; i < np; i++)
        {
            acc += f(a0 + dy * i);
        }
        I = (I_old + acc * dy) / 2.0;
        printf("I_%d = %f\n", l, I);
        if (fabs(I - I_old) < tol)
        {
            break;
        }
        I_old = I;
    }
    return I;
}