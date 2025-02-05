#include "stdio.h"
#include "math.h"

#define METHOD 0
#define M 80.0
#define G 9.81
#define GAMMA 5.38

// X = X, Y = Y, Z = dX/dt, W = dY/dt

double fx(double x, double y, double z, double w, double t)
{
    return z;
}
double fy(double x, double y, double z, double w, double t)
{
    return w;
}
double fz(double x, double y, double z, double w, double t)
{
    return -(GAMMA / M) * z * sqrt(z * z + w * w);
}
double fw(double x, double y, double z, double w, double t)
{
    return -G - (GAMMA / M) * w * sqrt(z * z + w * w);
}

int main()
{
    double x = 0;
    double y = 0;
    double z = 134;
    double w = 0;

    int L = 150;
    double dt = 0.01;
    for (int i = 0; i < L; i++)
    {
        if (METHOD == 0)
        {
            // Euler Method
            double t = i * dt;
            double dx = fx(x, y, z, w, t);
            double dy = fy(x, y, z, w, t);
            double dz = fz(x, y, z, w, t);
            double dw = fw(x, y, z, w, t);
            double x_new = x + dt * dx;
            double y_new = y + dt * dy;
            double z_new = z + dt * dz;
            double w_new = w + dt * dw;
            x = x_new;
            y = y_new;
            z = z_new;
            w = w_new;
            printf("Tempo: %f   ", t + dt);
            printf("Posicao X: %f, Velocidade X: %f   ", x, z);
            printf("Posicao Y: %f, Velocidade Y: %f\n", y, w);
        }
        else
        {
            // Euler Aprimorado
            double t = i * dt;
            double dx = fx(x, y, z, w, t);
            double dy = fy(x, y, z, w, t);
            double dz = fz(x, y, z, w, t);
            double dw = fw(x, y, z, w, t);
            double x_new = x + dt * dx;
            double y_new = y + dt * dy;
            double z_new = z + dt * dz;
            double w_new = w + dt * dw;
            double dx_new = fx(x_new, y_new, z_new, w_new, t + dt);
            double dy_new = fy(x_new, y_new, z_new, w_new, t + dt);
            double dz_new = fz(x_new, y_new, z_new, w_new, t + dt);
            double dw_new = fw(x_new, y_new, z_new, w_new, t + dt);
            x_new = x + dt * (dx + dx_new) / 2;
            y_new = y + dt * (dy + dy_new) / 2;
            z_new = z + dt * (dz + dz_new) / 2;
            w_new = w + dt * (dw + dw_new) / 2;
            x = x_new;
            y = y_new;
            z = z_new;
            w = w_new;
            printf("Tempo: %f   ", t + dt);
            printf("Posicao X: %f, Velocidade X: %f   ", x, z);
            printf("Posicao Y: %f, Velocidade Y: %f\n", y, w);
        }
    }

    return 0;
}