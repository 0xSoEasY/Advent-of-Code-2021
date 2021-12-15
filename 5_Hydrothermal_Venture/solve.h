#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Uncomment this line for the debug mode (using test_input.txt)
// #define DEBUG 1

#ifdef DEBUG
    #define DIAG_MAX_SIZE 10
#else
    #define DIAG_MAX_SIZE 1000
#endif


typedef struct {
    int x1;
    int x2;
    int y1;
    int y2;
} coords;
