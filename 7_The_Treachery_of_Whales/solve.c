#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Get the number of values separated by a delimiter */
int get_nb_positions(char* line, char delim){
    char* ptr = line;
    int nb_positions;
    
    for(nb_positions=0; ptr[nb_positions]; ptr[nb_positions]==delim ? nb_positions++ : *ptr++);

    return nb_positions + 1;
}


/* Convert a str to a int array using a delimiter */
void str_to_int_array(const char* delim, char* string, int* array){
    char* ptr = strtok(string, delim);

	for(int i=0; ptr != NULL; i++){
        array[i] = atoi(ptr);
        ptr = strtok(NULL, delim);
    }
}


/* Get the maximum value in a int array */
int max_value(int array[], int size){
    int max = array[0];

    for(int i=0; i < size; i++){
        if(array[i] > max){
            max = array[i];
        }
    }
    return max;
}


/* Get the minimum value in a int array */
int min_value(int array[], int size){
    int min = array[0];

    for(int i=0; i < size; i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    return min;
}



/*
 Entry point of the program
 */
int main(int argc, char** argv){

    FILE* fd;
    char line[4000];
    int nb_positions, max, min, tmp;

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


    fgets(line, sizeof(line), fd);
    nb_positions = get_nb_positions(line, ',');
    printf("[x] Number of values : %d\n", nb_positions);

    int positions[nb_positions];
    fseek(fd, 0, SEEK_SET);

    fgets(line, sizeof(line), fd);
    str_to_int_array(",", line, positions);
    fclose(fd);

    max = max_value(positions, nb_positions);
    min = min_value(positions, nb_positions);

    int fuel[max];
    memset(fuel, 0, max * sizeof(int));

    printf("[x] Max value : %d\n", max);
    printf("[x] Min value : %d\n", min);

    for(int i=0; i < max; i++){
        for(int j=0; j < nb_positions; j++){
            fuel[i] += abs(positions[j] - i);
        }
    }

    puts("------------------------------------------");
    printf("[+] Minmum fuel cost (part. 1) : %d\n", min_value(fuel, max));


    //////////////////////////////////////////////////////////////////////
    /////////////////////////////   PART 2   /////////////////////////////
    //////////////////////////////////////////////////////////////////////

    // reset fuel costs
    memset(fuel, 0, max * sizeof(int));

    tmp = 0;
    for(int i=0; i < max; i++){
        for(int j=0; j < nb_positions; j++){
            tmp = abs(positions[j] - i);
            
            // https://www.quora.com/How-do-you-write-a-program-in-C-language-to-find-the-sum-of-numbers-1-to-100
            fuel[i] += tmp * (tmp+1) / 2;
        }
    }

    printf("[+] Minmum fuel cost (part. 2) : %d\n", min_value(fuel, max));

    return EXIT_SUCCESS;
}