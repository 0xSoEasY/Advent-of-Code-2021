#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

  0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....


  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg


1  -->  2 segments (UNIQUE)
7  -->  3 segments (UNIQUE)
4  -->  4 segments (UNIQUE)

2  -->  5 segments 
3  -->  5 segments 
5  -->  5 segments 

0  -->  6 segments 
6  -->  6 segments 
9  -->  6 segments 

8  -->  7 segments (UNIQUE)

*/



/* Count the number of 1,4,7,8 in the output values */
int count_output_1_4_7_8(char* line){
    char* ptr;
    int total = 0;

    // Take only the part after the '|' (offset 61)
    while(*line != '|'){
        line++;
    }
    line += 2;

    ptr = strtok(line, " ");
    
    while(ptr != NULL){
        ptr[strcspn(ptr, "\n")] = 0;

        switch(strlen(ptr)) {
            case 2:
            case 3:
            case 4:
            case 7:
                total++;

            default:
                break;
        }
        ptr = strtok(NULL, " ");
    }
    return total;
}


int main(int argc, char** argv){

    FILE* fd;
    char line[128];
    int nb_1_4_7_8;

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


    nb_1_4_7_8 = 0;
    while(fgets(line, sizeof(line), fd)){
        nb_1_4_7_8 += count_output_1_4_7_8(line);
    }

    printf("[+] Number of 1,4,7,8 (part. 1) : %d\n", nb_1_4_7_8);


    //////////////////////////////////////////////////////////////////////
    /////////////////////////////   PART 2   /////////////////////////////
    //////////////////////////////////////////////////////////////////////


    fclose(fd);

    return EXIT_SUCCESS;
}