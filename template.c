#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

    FILE* fd;
    char line[128];

    if(argc < 2){
        printf("\tUsage : %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = fopen(argv[1], "r");

    if(fd == NULL){
        printf("[-] Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    while(fgets(line, sizeof(line), fd)){
        printf("%s", line);
    }

    return EXIT_SUCCESS;
}