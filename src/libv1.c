#include "contracts.h"
#include <math.h>

static float rect_integral(float A, float B, float e) {
    if (e <= 0.0f) return NAN;
    if (A > B) {
        float tmp = A; A = B; B = tmp;
    }
    long steps = (long)((B - A) / e);
    float x = A;
    float sum = 0.0f;
    for (long i = 0; i < steps; ++i) {
        sum += sinf(x) * e; // left rectangles
        x += e;
    }
    // handle remaining tail
    float tail = B - x;
    if (tail > 0) sum += sinf(x) * tail;
    return sum;
}

static void bubble_sort(int* arr, int n) {
    if (!arr || n <= 1) return;
    int swapped;
    do {
        swapped = 0;
        for (int i = 1; i < n; ++i) {
            if (arr[i-1] > arr[i]) {
                int t = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = t;
                swapped = 1;
            }
        }
        --n;
    } while (swapped);
}

float SinIntegral(float A, float B, float e) {
    return rect_integral(A, B, e);
}

int* Sort(int* array, int length) {
    bubble_sort(array, length);
    return array;
}
