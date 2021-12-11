#include <stdio.h>
#include <stdlib.h>

#define DATASET_SIZE 2000

/* Solution for part 1 : number of increases */
int part_1(int* dataset){
    int nb_increase, current, last;

    nb_increase = 0;
    current = last = dataset[0];

    for(int i=0; i < DATASET_SIZE; i++){
        current = dataset[i];
        
        if(current > last){
            nb_increase++;
        }
        
        last = current;
    }
    return nb_increase;
}


/* Solution for part 2 : number of increases by group of 3 */
int part_2(int* dataset){
    int current[3], last[3];
    int nb_increase = 0;
    int total_last, total_current;

    last[0] = dataset[0];
    last[1] = dataset[1];
    last[2] = dataset[2];

    for(int i=1; i < DATASET_SIZE - 2; i++){
        current[0] = dataset[i];
        current[1] = dataset[i + 1];
        current[2] = dataset[i + 2];

        total_last = last[0] + last[1] + last[2];
        total_current = current[0] + current[1] + current[2];

        if(total_current > total_last){
            nb_increase++;
        }
        
        last[0] = current[0];
        last[1] = current[1];
        last[2] = current[2];
    }

    return nb_increase;
}


int main(int argc, char** argv){

    FILE* fd;
    char line[10];
    int last, current;

    if(argc < 2){
        printf("\tUsage : %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = fopen(argv[1], "r");

    if(fd == NULL){
        printf("[-] Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Convert the file to a int[]
    int dataset[DATASET_SIZE];
    for(int i=0; fgets(line, sizeof(line), fd); i++){
        dataset[i] = atoi(line);
    }
    
    fclose(fd);

    printf("[+] Total of increases (part. 1) : %d\n", part_1(dataset));
    printf("[+] Total of increases by group of 3 (part. 2) : %d\n", part_2(dataset));

    return EXIT_SUCCESS;
}