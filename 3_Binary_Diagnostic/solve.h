#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INT_SIZE 32
#define INPUT_SIZE 12

#define USED 1
#define NOT_USED 0

#define OXYGEN_CHECK 42
#define CO2_CHECK 666

int nb_lines = 0;

typedef struct {
    int used_oxygen;
    int used_co2;
    // 12 bits (character '0' or '1') + '\n\0'
    char value[INPUT_SIZE + 2];
} bin_value;