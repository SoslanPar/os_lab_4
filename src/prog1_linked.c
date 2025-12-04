#include <stdio.h>
#include <stdlib.h>
#include "contracts.h"

static void cmd_integral(int argc, char** argv) {
    if (argc < 4) { printf("Usage: 1 A B e\n"); return; }
    float A = (float)atof(argv[1]);
    float B = (float)atof(argv[2]);
    float e = (float)atof(argv[3]);
    float res = SinIntegral(A, B, e);
    printf("Integral: %f\n", res);
}

static void cmd_sort(int argc, char** argv) {
    if (argc < 2) { printf("Usage: 2 n x1 x2 ... xn\n"); return; }
    int n = atoi(argv[1]);
    if (argc < 2 + n) { printf("Not enough numbers for n=%d\n", n); return; }
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) arr[i] = atoi(argv[2 + i]);
    Sort(arr, n);
    printf("Sorted:");
    for (int i = 0; i < n; ++i) printf(" %d", arr[i]);
    printf("\n");
    free(arr);
}

int main(void) {
    // Program #1: linked against one shared library at link-time (v1 by default via Makefile)
    // Input loop: "1 A B e" or "2 n x1 ... xn"
    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        // tokenize by spaces/tabs/newlines
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
        if (argv[0][0] == '1') {
            cmd_integral(argc, argv);
        } else if (argv[0][0] == '2') {
            cmd_sort(argc, argv);
        } else {
            printf("Unknown command. Use '1' or '2'.\n");
        }
    }
    return 0;
}