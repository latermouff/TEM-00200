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

double secant(double (*f)(double), double x0, double x1, int limit)
{
    int it = 0;

#if DEBUG == 1
    printf("%d,%lf\n", it - 1, x0);
    printf("%d,%lf\n", it, x1);
#endif
    double fn;
    while (it < limit && (fn = f(x1), fabs(x1 - x0) > TOL(x1) && fabs(fn) > TOL(fn)))
    {
        double fd = f(x1) - f(x0);
        fn *= (x1 - x0);
        if (fabs(fd) < TOL(fn))
        {
            printf("Secant Method failed!\n");
            return x1;
        }
        x0 = x1;
        x1 -= fn / fd;
        ++it;
#if DEBUG == 1
        printf("%d,%lf\n", it, x1);
#endif
    }
    return x1;
}

int main()
{
    double res = secant(f, 0.0, 1.0, 1000);

    printf("Final Result: %f\n", res);

    return 0;
}