#include <iostream>
#include <cstdlib>
#include <cmath>
#include <immintrin.h>
#include <omp.h>

#define SIZE 50000
#define REAL 0
#define IMAG 1

int main() {
    auto a = new float[SIZE][2];
    auto b = new float[SIZE][2];
    auto c = new float[SIZE][2]();
    double n = SIZE;
    double seed = 3.141592653589793;

    for (int i = 0; i < SIZE; i++) {
        a[i][REAL] = sin((seed * i * (seed * i + 1) * (2 * seed * i + 1)) / 6);
        a[i][IMAG] = cos((seed * i * (seed * i + 1) * (2 * seed * i + 1)) / 6);
        b[i][REAL] = sin((6 * seed * i * (seed * i - 1) + 1));
        b[i][IMAG] = cos((6 * seed * i * (seed * i - 1) + 1));
    }

    double t = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j += 8) {
            __m256 a_real = _mm256_set1_ps(a[i][REAL]);
            __m256 a_imag = _mm256_set1_ps(a[i][IMAG]);
            __m256 b_real = _mm256_loadu_ps(&b[j][REAL]);
            __m256 b_imag = _mm256_loadu_ps(&b[j][IMAG]);
            __m256 c_real = _mm256_fmsub_ps(a_real, b_real, _mm256_mul_ps(a_imag, b_imag)); 
            __m256 c_imag = _mm256_fmadd_ps(a_imag, b_real, _mm256_mul_ps(a_real, b_imag));
            _mm256_storeu_ps(&c[i][REAL], c_real);
            _mm256_storeu_ps(&c[i][IMAG], c_imag);
        }
    }

    t = omp_get_wtime() - t;

    printf("Time elapsed to execute program: %.2f seconds\n", t);

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

