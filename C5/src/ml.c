#include "stdio.h"
#include "stdlib.h"

#define IDX2(i, j, L) ((i) * (L) + (j))

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

void BS(double *x, double *U, double *b, int L)
{
    for (int i = L - 1; i >= 0; i--)
    {
        double acc = b[i];
        for (int j = L - 1; j > i; j--)
        {
            acc -= U[IDX2(i, j, L)] * x[j];
        }
        x[i] = acc / U[IDX2(i, i, L)];
    }
}

void Gauss(double *x, double *A, double *b, int L)
{
    PrintMatrix(A, L, L);
    printf("\n");
    PrintMatrix(b, L, 1);
    printf("\n");
    for (int k = 0; k < L; k++)
    {
        double aux = A[IDX2(k, k, L)];
        for (int i = k + 1; i < L; i++)
        {
            double c = A[IDX2(i, k, L)] / aux;
            for (int j = k; j < L; j++)
            {
                A[IDX2(i, j, L)] -= c * A[IDX2(k, j, L)];
            }
            b[i] -= c * b[k];
        }
    }
    BS(x, A, b, L);
    PrintMatrix(A, L, L);
    printf("\n");
    PrintMatrix(x, L, 1);
    printf("\n");
}

void LU(double *x, double *A, double *b, int L)
{
    double *L_m = malloc(sizeof(double) * L * L);
    for (int k = 0; k < L; k++)
    {
        double aux = A[IDX2(k, k, L)];
        for (int i = k + 1; i < L; i++)
        {
            double c = A[IDX2(i, k, L)] / aux;
            L_m[IDX2(i, k, L)] = c;
            for (int j = k; j < L; j++)
            {
                A[i, j] -= c * A[k, j];
            }
        }
    }
}

int main()
{
    int m, n;
    m = 2;
    n = 2;
    double *A = malloc(sizeof(double) * m * n);
    double *b = malloc(sizeof(double) * m);
    double *x = malloc(sizeof(double) * n);
    A[IDX2(0, 0, n)] = 2;
    A[IDX2(1, 0, n)] = 3;
    A[IDX2(0, 1, n)] = 3;
    A[IDX2(1, 1, n)] = 4;
    b[0] = 1;
    b[1] = 1;
    Gauss(x, A, b, m);

    return 0;
}