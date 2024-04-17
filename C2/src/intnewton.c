#include "stdio.h"

void newtonCoefficients(double *coefs, double *x, double *y, int n)
{
    for (int j = 0; j < n; j++)
    {
        coefs[j] = y[j];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            coefs[i * n + j] = (coefs[(i - 1) * n + j + 1] - coefs[(i - 1) * n + j]) / (x[j + i] - x[j]);
        }
    }
    return;
}

double newton(double *coefs, double *x, double *y, int n, double val)
{
    double acc = 0.0;
    for (int i = 0; i < n; i++)
    {
        double termo = coefs[i * n];
        for (int j = 0; j < i; j++)
        {
            termo = termo * (val - x[j]);
        }
        acc += termo;
    }
    return acc;
}

int main()
{
    int n = 4;
    double x[4] = {0.0, 1.0, 2.0, 3.0};
    double y[4] = {0.0, 1.0, 4.0, 9.0};

    double coefs[n * n];
    newtonCoefficients(coefs, x, y, n);

    double x_min = 0.0;
    double x_max = 3.0;
    double m = 20;
    double dx = (x_max - x_min) / (m - 1);
    for (int i = 0; i < m; i++)
    {
        double x_i = dx * i + x_min;
        double res = newton(coefs, x, y, n, x_i);
        printf("%lf,%lf\n", x_i,res);
    }
}