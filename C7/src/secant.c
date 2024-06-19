#include "stdio.h"
#include "math.h"

#define TOL 1e-6

double f(double re, double pr, double nu)
{
    double a0 = 0.3;
    double a1 = 0.62 * sqrt(re) * pow(pr, 1.0 / 3.0);
    double a2 = pow(1 + pow(0.4 / pr, 2.0 / 3.0), 1.0 / 4.0);
    double a3 = pow(1 + pow(re / 282000.0, 5.0 / 8.0), 4.0 / 5.0);
    return a0 + (a1 / a2) * a3 - nu;
}

double secant(double x1, double x2, double pr, double nu)
{
    double x;
    do
    {
        x = x1 - f(x1, pr, nu) * (x1 - x2) / (f(x1, pr, nu) - f(x2, pr, nu));
        x2 = x1;
        x1 = x;
    } while (fabs(x1 - x2) > TOL);
    return x;
}

int main()
{
    int L = 5;
    double Pr_0, Pr_1;
    Pr_0 = 5.25;
    Pr_1 = 6.25;
    printf("\tPr\tNu\tRe_d\n");
    for (int i = 0; i < L; i++)
    {
        double pr = Pr_0 + i * (Pr_1 - Pr_0) / (L - 1);
        double nu = 1e3;
        double re = secant(1.01e5, 1.00e5, pr, nu);
        printf("%d\t%.2f\t%.0f\t%.1f\n",i,pr,nu,re);
    }
    return 0;
}