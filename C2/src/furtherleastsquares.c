#include "stdio.h"
#include "math.h"

typedef double (*base)(double);

void printMatrix(double *A, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%lf, ", A[j * n + i]);
        }
        printf("\n");
    }
}

void SolveSymLin(double *A, double *B, int N, int M)
{
    // Decompose Matrix
    for (int j = 0; j < N; j++)
    {
        double sum = 0;
        for (int k = 0; k < j; k++)
        {
            sum += A[k * N + j] * A[k * N + j];
        }
        A[j * N + j] = sqrt(A[j * N + j] - sum);

        for (int i = j + 1; i < N; i++)
        {
            sum = 0;
            for (int k = 0; k < j; k++)
            {
                sum += A[k * N + i] * A[k * N + j];
            }
            A[j * N + i] = (1.0 / A[j * N + j] * (A[j * N + i] - sum));
        }
    }
    // Solve Linear System - Forward Normal/Backward Transpose
    for (int j = 0; j < M; j++)
    {
        // Forward Normal
        for (int i = 0; i < N; i++)
        {
            double acc = 0.0;
            for (int k = 0; k < i; k++)
            {
                acc += A[k * N + i] * B[j * N + k];
            }
            B[j * N + i] = (B[j * N + i] - acc) / A[i * N + i];
        }
        // Backward Transpose
        for (int i = 0; i < N; i++)
        {
            int ii = N - i - 1;
            double acc = 0.0;
            for (int k = 0; k < i; k++)
            {
                int kk = N - k - 1;
                acc += A[ii * N + kk] * B[j * N + kk];
            }
            B[j * N + ii] = (B[j * N + ii] - acc) / A[ii * N + ii];
        }
    }
}

void matmulNN(double *C, double *A, double *B, int M, int N, int K)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            double acc = 0.0;
            for (int k = 0; k < K; k++)
            {
                acc += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = acc;
        }
    }
}
void matmulNT(double *C, double *A, double *B, int M, int N, int K)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            double acc = 0.0;
            for (int k = 0; k < K; k++)
            {
                acc += A[i * K + k] * B[j * K + k];
            }
            C[i * N + j] = acc;
        }
    }
}

void furtherleastSquares(base *f, double *coefs, int n_coef, double *x, double *y, int n)
{
    double A[n_coef * n];
    for (int i = 0; i < n_coef; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i * n + j] = f[i](x[j]);
        }
    }
    double B[n_coef * n_coef];
    matmulNT(B, A, A, n_coef, n_coef, n);
    matmulNT(coefs, A, y, n_coef, 1, n);
    SolveSymLin(B, coefs, n_coef, 1);
    return;
}

double f0(double x)
{
    return 1.0;
}
double f1(double x)
{
    return x;
}

int main()
{
    int n = 4;
    double x[4] = {0.0, 1.0, 2.0, 3.0};
    double y[4] = {0.0, 1.0, 4.0, 9.0};

    int n_coef = 2;
    base f[2] = {&f0, &f1};
    double coefs[2];
    furtherleastSquares(f, coefs, n_coef, x, y, n);
    printf("Coefficients: ");
    for (int i = 0; i < n_coef; i++)
    {
        printf("%lf, ", coefs[i]);
    }
    printf("\n");

    double x_min = 0.0;
    double x_max = 3.0;
    double m = 20;
    double dx = (x_max - x_min) / (m - 1);
    for (int i = 0; i < m; i++)
    {
        double x_i = dx * i + x_min;
        double res = 0.0;
        for (int i = 0; i < n_coef; i++)
        {
            res += coefs[i] * f[i](x_i);
        }
        printf("%lf,%lf\n", x_i, res);
    }
}