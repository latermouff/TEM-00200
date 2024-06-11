#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define K 1.0
#define M 1.0

double euler_step(double x0, double y0, double dx, double (*f)(double, double))
{
    return y0 + dx * f(x0, y0);
}

void euler_vstep(double x, double *uf, double *u, int n, double dx, void (*f)(double, double *, double *))
{
    double du[n];
    f(x, u, du);
    for (int i = 0; i < n; i++)
    {
        uf[i] = u[i] + dx * du[i];
    }
}

void euler(double *p_y, double (*f)(double, double), double x0, double y0, double xf, int n)
{
    double dx = (xf - x0) / n;
    *p_y = y0;
    for (int i = 0; i < n; i++)
    {
        double x = x0 + i * dx;
        *p_y = euler_step(x, *p_y, dx, f);
    }
}

void eulerV(double *u, int Lu, void (*f)(double, double *, double *), double x0, double xf, int n)
{
    double dx = (xf - x0) / n;
    for (int i = 0; i < n; i++)
    {
        double x = x0 + i * dx;
        euler_vstep(x, u + (i + 1) * Lu, u + i * Lu, Lu, dx, f);
    }
}

double testY(double x, double y)
{
    return y;
}
double testExp(double x, double y)
{
    return exp(x);
}

void testVector(double x, double *u, double *du)
{
    du[0] = u[1];
    du[1] = -((double)K / (double)M) * u[0];
}

int main()
{
    int n = 1000;
    double *u = (double *)malloc(sizeof(double) * 2 * (n + 1));
    u[0] = 1.0;
    u[1] = 0.0;
    eulerV(u, 2, testVector, 0.0, 10.0, n);

    FILE *file = NULL;
    file = fopen("data.dat", "w");
    for (int i = 0; i <= n; i++)
    {
        fprintf(file,"%.8f\t%.8f\n", u[2 * i], u[2 * i + 1]);
    }
    fclose(file);
    free(u);
    return 0;
}