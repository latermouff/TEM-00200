#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define ATOL (1e-8)
#define RTOL (1e-6)
#define TOL(x) (ATOL + (RTOL * (x)))

#define IDX2(i, j, n) ((i) * (n) + j)

void PrintMatrix(double *A, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", A[IDX2(i, j, n)]);
        }
        printf("\n");
    }
}

double difnorm2(double *a, double *b, int L)
{
    double acc = 0.0;
    for (int i = 0; i < L; i++)
    {
        acc += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(acc);
}

void seidel(double *x, double *A, double *b, double *x0, int L)
{
    double *xold = malloc(sizeof(double) * L);
    for (int i = 0; i < L; i++)
    {
        x[i] = x0[i];
    }
    int aux = 0;
    do
    {
        for (int i = 0; i < L; i++)
        {
            xold[i] = x[i];
        }
        for (int i = 0; i < L; i++)
        {
            double acc = 0.0;
            for (int j = 0; j < i; j++)
            {
                acc += A[IDX2(i, j, L)] * x[j];
            }
            for (int j = i + 1; j < L; j++)
            {
                acc += A[IDX2(i, j, L)] * xold[j];
            }
            x[i] = (b[i] - acc) / A[IDX2(i, i, L)];
        }
        PrintMatrix(x,1,L);
        aux++;
    } while (difnorm2(x, xold, L) > TOL(1.0));
    printf("Iterations: %d\n",aux);
}

int main()
{
    int L = 10;
    double *A = malloc(sizeof(double) * L * L);
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            if (i == j)
            {
                A[IDX2(i, j, L)] = -2.0;
            }
            else if (i == j + 1 || i + 1 == j)
            {
                A[IDX2(i, j, L)] = 1.0;
            }
            else
            {
                A[IDX2(i, j, L)] = 0.0;
            }
        }
    }
    double *b = malloc(sizeof(double) * L);
    for (int i = 0; i < L; i++)
    {
        b[i] = 0.0;
    }
    b[0]=100.0;
    double *x = malloc(sizeof(double) * L);

    seidel(x,A,b,b,L);
    PrintMatrix(x,L,1);
    return 0;
}