#include "stdio.h"

void leastSquares(double *alpha, double *beta, double *x, double *y, int n)
{
    double Sx = 0.0, Sxx = 0.0, Sy = 0.0, Sxy = 0.0;
    for (int i = 0; i < n; i++)
    {
        Sx += x[i];
        Sxx += x[i] * x[i];
        Sy += y[i];
        Sxy += x[i] * y[i];
    }
    double d = (n * Sxx - Sx * Sx);
    *alpha = (n * Sxy - Sx * Sy) / d;
    *beta = (Sy * Sxx - Sx * Sxy) / d;
    return;
}

int main()
{
    int n = 4;
    double x[4] = {0.0, 1.0, 2.0, 3.0};
    double y[4] = {0.0, 1.0, 4.0, 9.0};

    double alpha, beta;
    leastSquares(&alpha, &beta, x, y, n);
    printf("Alpha = %lf, Beta = %lf\n", alpha, beta);

    double x_min = 0.0;
    double x_max = 3.0;
    double m = 20;
    double dx = (x_max - x_min) / (m - 1);
    for (int i = 0; i < m; i++)
    {
        double x_i = dx * i + x_min;
        double res = alpha * x_i + beta;
        printf("%lf,%lf\n", x_i, res);
    }
}