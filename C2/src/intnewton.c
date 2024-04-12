#include "stdio.h"

double newton(double *x, double *y, int n, double val)
{
    double coefs[n * n];
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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf,", coefs[i * n + j]);
        }
        printf("\n");
    }
    return acc;
}

int main()
{
    int n = 4;
    double x[4] = {0.0, 1.0, 2.0, 3.0};
    double y[4] = {0.0, 1.0, 2.0, 3.0};

    double res = newton(x, y, 4, 0.5);
    printf("%lf\n", res);
}