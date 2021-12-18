#include "solve.h"

/* Compute a day for part. 1 (using a linked list of lanternfish) */
lanternfish* apply_day_part1(lanternfish* first, lanternfish* last){
    lanternfish* ptr = first;
    lanternfish* ptr_last = last;

    while(ptr != NULL){
        if(ptr->value == 0){
            ptr->value = 6;

            ptr_last->next = malloc(sizeof(lanternfish));
            ptr_last = ptr_last->next;
            ptr_last->value = 9;
        
        }else{
            ptr->value -= 1;
        }
        ptr = ptr->next;
    }
    return ptr_last;
}


/* Compute a day for part. 2 (using a long internal_timers[9]) */
void apply_day_part2(long internal_timers[9]){
    long tmp[9];
    memset(tmp, 0, 9*sizeof(long));

    for(int i=8; i >= 0; i--){
        if(i == 0){
            tmp[6] += internal_timers[0];
            tmp[8] += internal_timers[0];

        }else{
            tmp[i-1] = internal_timers[i];
        }
    }

    memcpy(internal_timers, tmp, 9*sizeof(long));
}


/*
 Entry point of the program
 */
int main(int argc, char** argv){

    FILE* fd;
    char input_number;

    if(argc < 2){
        printf("\tUsage : %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = fopen(argv[1], "r");

    if(fd == NULL){
        printf("[-] Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }


    //////////////////////////////////////////////////////////////////////
    /////////////////////////////   PART 1   /////////////////////////////
    //////////////////////////////////////////////////////////////////////

    /*
    This part is using the naive method : using a linked list of "lanternfish" structures
    */

    lanternfish* first;
    lanternfish* last;

    first = malloc(sizeof(lanternfish));
    first->value = fgetc(fd) - 0x30;
    last = first;

    while((input_number = fgetc(fd)) != EOF){
        if(input_number != ','){
            last->next = malloc(sizeof(lanternfish));
            last = last->next;
            last->value = input_number - 0x30; // -0x30 to convert '8' to 8
        }
    }


    for(int i=0; i < 80; i++){
        last = apply_day_part1(first, last);

        #ifdef DEBUG
            print_fishes_part1(first);
        #endif
    }

    printf("[+] Number of fishes in 80 days (part. 1) : %d\n", count_fishes_part1(first));


    //////////////////////////////////////////////////////////////////////
    /////////////////////////////   PART 2   /////////////////////////////
    //////////////////////////////////////////////////////////////////////

    /*
    In this second part, we will need a more efficient way to solve this problem : using a long[9] array
    */

    // Here we go again...
    fseek(fd, 0, SEEK_SET);

    long lanternfish_internal_timers[9];
    memset(lanternfish_internal_timers, 0, 9 * sizeof(long));

    while((input_number = fgetc(fd)) != EOF){
        if(input_number != ','){
            lanternfish_internal_timers[input_number - 0x30]++; // -0x30 to convert '8' to 8
        }
    }

    fclose(fd);

    for(int i=0; i < 256; i++){
        apply_day_part2(lanternfish_internal_timers);

        #ifdef DEBUG
            print_fishes_part2(lanternfish_internal_timers);
        #endif
    }

    printf("[+] Number of fishes in 256 days (part. 2) : %ld\n", count_fishes_part2(lanternfish_internal_timers));

    return EXIT_SUCCESS;
}