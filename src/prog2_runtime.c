#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
// #include "contracts.h"

typedef float (*pSinIntegral)(float, float, float);
typedef int* (*pSort)(int*, int);

static pSinIntegral fSinIntegral = NULL;
static pSort fSort = NULL;
static void* currentLib = NULL;

static int load_library(const char* path) {
    // dlopen загружает библиотеку в память, возвращает дескриптор бибилотеки.
    // RTLD_NOW — разрешить все символы (например, математические) сразу
    void* h = dlopen(path, RTLD_NOW);

    if (!h) { printf("Failed to load: %s (%s)\n", path, dlerror()); return 0; }
    dlerror();

    // dlsym ищет функцию по имени, возвращает её адрес в памяти
    pSinIntegral si = (pSinIntegral)dlsym(h, "SinIntegral");
    pSort so = (pSort)dlsym(h, "Sort");

    const char* err = dlerror();
    if (err) { printf("Missing symbols: %s\n", err); dlclose(h); return 0; }
    if (currentLib) dlclose(currentLib);

    currentLib = h;
    fSinIntegral = si; fSort = so;
    printf("Loaded %s\n", path);
    return 1;
}

static void unload_library(void) {
    if (currentLib) {
        dlclose(currentLib);
        currentLib = NULL;
    }
}

// function pointers declared above

static void cmd_integral(int argc, char** argv) {
    if (!fSinIntegral) { printf("No library loaded\n"); return; }
    if (argc < 4) { printf("Usage: 1 A B e\n"); return; }
    float A = (float)atof(argv[1]);
    float B = (float)atof(argv[2]);
    float e = (float)atof(argv[3]);
    float res = fSinIntegral(A, B, e);
    printf("Integral: %f\n", res);
}

static void cmd_sort(int argc, char** argv) {
    if (!fSort) { printf("No library loaded\n"); return; }
    if (argc < 2) { printf("Usage: 2 n x1 x2 ... xn\n"); return; }
    int n = atoi(argv[1]);
    if (argc < 2 + n) { printf("Not enough numbers for n=%d\n", n); return; }
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) arr[i] = atoi(argv[2 + i]);
    fSort(arr, n);
    printf("Sorted:");
    for (int i = 0; i < n; ++i) printf(" %d", arr[i]);
    printf("\n");
    free(arr);
}

int main(void) {
    // Start with v1 by default
    load_library("./libv1.so");
    char line[1024];
    int useV1 = 1;
    while (fgets(line, sizeof(line), stdin)) {
        char* argv[128]; int argc = 0;
        char* p = line;
        while (*p) {
            while (*p && (*p==' '||*p=='\t'||*p=='\n')) ++p;
            if (!*p) break;
            argv[argc++] = p;
            while (*p && *p!=' ' && *p!='\t' && *p!='\n') ++p;
            if (*p) { *p = '\0'; ++p; }
        }
        if (argc == 0) continue;
        if (argv[0][0] == '0') {
            if (useV1) { load_library("./libv2.so"); useV1 = 0; }
            else { load_library("./libv1.so"); useV1 = 1; }
        } else if (argv[0][0] == '1') {
            cmd_integral(argc, argv);
        } else if (argv[0][0] == '2') {
            cmd_sort(argc, argv);
        } else {
            printf("Unknown command. Use '0', '1', or '2'.\n");
        }
    }
    unload_library();
    return 0;
}
