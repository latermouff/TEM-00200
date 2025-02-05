#include "stdio.h"
#include "math.h"

#define METHOD 1

#define G 9.8
#define LENGTH 0.1
// X = Theta, Y = d Theta / dt

double fx(double x, double y, double t)
{
    return y;
}
double fy(double x, double y, double t)
{
    return -G * sin(x) / LENGTH;
}

int main()
{
    double x = 0;
    double y = 1;

    int L = 20;
    double dt = 0.01;
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
            printf("Time: %f, Theta: %f, d Theta/dt: %f\n", t + dt, x, y);
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
            printf("Time: %f, Theta: %f, d Theta/dt: %f\n", t + dt, x, y);
        }
    }

    return 0;
}