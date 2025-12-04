#pragma once

#define DLL_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

// Function #1: integral of sin(x) on [A, B] with step e
DLL_EXPORT float SinIntegral(float A, float B, float e);

// Function #2: sort int array in-place
// Returns pointer to the same array for convenience
DLL_EXPORT int* Sort(int* array, int length);

#ifdef __cplusplus
}
#endif
