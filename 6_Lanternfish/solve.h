#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG 1

struct lanternfish {
    int value;
    struct lanternfish* next;
};

// YOLO
#define lanternfish struct lanternfish


/* Print all the lanterfishes in the linked list (used for debug) */
void print_fishes_part1(lanternfish* first){
    lanternfish* ptr = first;

    while(ptr != NULL){
        printf("%d,", ptr->value);
        ptr = ptr->next;
    }
    puts("");
}


/* Print the number of fishes with every intern counter (used for debug) */
void print_fishes_part2(long internal_timers[9]){
    puts("---------------------------------------------------------");
    for(int i=0; i < 9; i++){
        printf("Number of fishes with %d as an intern counter : %ld\n", i, internal_timers[i]);
    }
}


/* Count the number of lanternfishes in a linked list of lanternfish */
int count_fishes_part1(lanternfish* first){
    lanternfish* ptr = first;
    int total = 0;

    while(ptr != NULL){
        total++;
        ptr = ptr->next;
    }
    return total;
}


/* Count the number of lanternfish in a internal_timer array */
long count_fishes_part2(long internal_timers[9]){
    long total = 0;

    for(int i=0; i < 9; i++){
        total += internal_timers[i];
    }
    return total;
}