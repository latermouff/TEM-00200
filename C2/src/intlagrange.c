#include "stdio.h"

double lagrange(double *x, double *y, int n, double val)
{
    double acc = 0.0;
    for (int i = 0; i < n; i++)
    {
        double termo = y[i];
        for (int j = 0; j < i; j++)
        {
            termo = termo * (val - x[j]) / (x[i] - x[j]);
        }
        for (int j = i + 1; j < n; j++)
        {
            termo = termo * (val - x[j]) / (x[i] - x[j]);
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

    double x_min = 0.0;
    double x_max = 3.0;
    double m = 20;
    double dx = (x_max - x_min) / (m - 1);
    for (int i = 0; i < m; i++)
    {
        double x_i = dx * i + x_min;
        double res = lagrange(x, y, n, x_i);
        printf("%lf,%lf\n", x_i, res);
    }
}