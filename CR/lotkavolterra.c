#include "stdio.h"

#define METHOD 0
#define ALPHA 0.1
#define BETA 0.02
#define GAMMA 0.3
#define DELTA 0.01

// X = Presas, Y = Predadores

double fx(double x, double y, double t)
{
    return x * (ALPHA - BETA * y);
}
double fy(double x, double y, double t)
{
    return y * (DELTA * x - GAMMA);
}

int main()
{
    double x = 10;
    double y = 10;

    int L = 1000;
    double dt = 0.1;
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
            printf("Presas: %f, Predadores: %f\n", x, y);
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
            printf("Presas: %f, Predadores: %f\n", x, y);
        }
    }

    return 0;
}