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
double fx(double x)
{
    return 2 * (x - 2.0);
}

double newton(double (*f)(double), double (*fx)(double), double x, int limit)
{
    int it = 0;

#if DEBUG == 1
    printf("%d,%lf\n", it, x);
#endif
    double fn;
    while (it < limit && (fn = f(x), fabs(fn) > TOL(fn)))
    {
        double fd = fx(x);
        if (fabs(fd) < TOL(fn))
        {
            printf("Newton Method failed!\n");
            return x;
        }
        x -= fn / fd;
        ++it;
#if DEBUG == 1
        printf("%d,%lf\n", it, x);
#endif
    }
    return x;
}

int main()
{
    double res = secant(f, 0.0, 1.0, 1000);

    printf("Final Result: %f\n", res);

    return 0;
}