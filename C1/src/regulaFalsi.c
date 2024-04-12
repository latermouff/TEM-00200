#include "stdio.h"
#include "math.h"

#define ATOL (1e-8)
#define RTOL (1e-6)
#define TOL(val) (ATOL + RTOL * (val))

#define DEBUG 1

double f(double x)
{
    return (x - 2.0) * (x - 2.0);
}

double bisection(double (*f)(double), double x0, double x1)
{
    double f0, f1;
    f0 = f(x0), f1 = f(x1);
    if (!(f0 * f1 < 0))
    {
        printf("Regula Falsi Method failed!\n");
        return NAN;
    }
    int it = 0;

#if DEBUG == 1
    printf("%d,%lf,%lf,%lf,%lf,%lf,%lf\n", it, x0, x1, (x0 + x1) / 2.0, f(x0), f(x1), f((x0 + x1) / 2.0));
#endif
    double c, fc;
    while (fabs(x1 - x0) > TOL(x1))
    {
        double fd = (f1 - f0);
        double fn = (x0 * f1 - x1 * f0);
        if (fabs(fd) < TOL(fn))
        {
            printf("Regula Falsi Method failed!\n");
            return x1;
        }
        c = fn / fd;
        fc = f(c);
        ++it;
#if DEBUG == 1
        printf("%d,%lf,%lf,%lf,%lf,%lf,%lf\n", it, x0, x1, c, f0, f1, fc);
#endif
        if (f0 * fc > 0.0)
        {
            x0 = c;
            f0 = fc;
        }
        else if (f1 * fc > 0.0)
        {
            x1 = c;
            f1 = fc;
        }
        else
        {
            return c;
        }
    }
    return (x0 + x1) / 2.0;
}

int main()
{
    double res = bisection(f, 0.0, 1.0);

    printf("Final Result: %f\n", res);

    return 0;
}