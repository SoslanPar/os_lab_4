#include "contracts.h"
#include <math.h>

static float trap_integral(float A, float B, float e) {
    if (e <= 0.0f) return NAN;
    if (A > B) {
        float tmp = A; A = B; B = tmp;
    }
    long steps = (long)((B - A) / e);
    float x = A;
    float sum = 0.0f;
    for (long i = 0; i < steps; ++i) {
        float x1 = x;
        float x2 = x + e;
        sum += (sinf(x1) + sinf(x2)) * 0.5f * e;
        x = x2;
    }
    float tail = B - x;
    if (tail > 0) sum += (sinf(x) + sinf(B)) * 0.5f * tail;
    return sum;
}

static void quicksort(int* a, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    int pivot = a[left + (right - left) / 2];
    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i <= j) {
            int t = a[i]; a[i] = a[j]; a[j] = t;
            ++i; --j;
        }
    }
    if (left < j) quicksort(a, left, j);
    if (i < right) quicksort(a, i, right);
}

float SinIntegral(float A, float B, float e) {
    return trap_integral(A, B, e);
}

int* Sort(int* array, int length) {
    if (array && length > 1) quicksort(array, 0, length - 1);
    return array;
}
