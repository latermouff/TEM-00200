#include "stdio.h"
#include "math.h"

#define METHOD 0

#define C1 3438336.0
#define C2 2412000.0
#define hc 1000.0
#define hinf 200.0
#define Tinf 27.0
#define r1 0.025
#define r2 0.035

// X = T1, Y = T2

// dX / dt = d T1 / dt
double fx(double x, double y, double t)
{
    return (2 * hc / (C1 * r1)) * (y - x);
}

// dY / dt = d T2 / dt
double fy(double x, double y, double t)
{
    return (1 / C2) * ((2 * hc / r1) * (x - y) + (2 * hinf * r2 / (r2 * r2 - r1 * r1)) * (Tinf - y));
}

int main()
{
    double x = 70;
    double y = 70;

    int L = 4;
    double dt = 5;
    for (int i = 0; i < L; i++)
    {
        if (METHOD == 0)
        {
            // Euler Method
            double t = i * dt;
            double dx = fx(x, y, t);
            double dy = fy(x, y, t);
            double x_new = x + dt * dx;
            double y_new = y + dt * dy;
            x = x_new;
            y = y_new;
            printf("Time: %f, T1: %f, T2: %f\n", t + dt, x, y);
        }
        else
        {
            // Euler Aprimorado
            double t = i * dt;
            double dx = fx(x, y, t);
            double dy = fy(x, y, t);
            double x_new = x + dt * dx;
            double y_new = y + dt * dy;
            double dx_new = fx(x_new, y_new, t + dt);
            double dy_new = fy(x_new, y_new, t + dt);
            x_new = x + dt * (dx + dx_new) / 2;
            y_new = y + dt * (dy + dy_new) / 2;
            x = x_new;
            y = y_new;
            printf("Time: %f, T1: %f, T2: %f\n", t + dt, x, y);
        }
    }

    return 0;
}