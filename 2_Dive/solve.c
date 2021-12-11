#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

    FILE* fd;
    char line[128];
    int horizontal, depth_1, depth_2, aim, tmp;
    char* ptr;

    if(argc < 2){
        printf("\tUsage : %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = fopen(argv[1], "r");

    if(fd == NULL){
        printf("[-] Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    horizontal = depth_1 = depth_2 = aim = 0;
    
    while(fgets(line, sizeof(line), fd)){
        // printf("%s", line);
        if(!strncmp(line, "forward", strlen("forward"))){
            ptr = line + strlen("forward") + 1;
            tmp = atoi(ptr);
            
            horizontal += tmp;
            depth_2 += (aim * tmp);
        
        }else if(!strncmp(line, "down", strlen("down"))){
            ptr = line + strlen("down") + 1;
            tmp = atoi(ptr);

            depth_1 += tmp;
            aim += tmp;
        
        }else if(!strncmp(line, "up", strlen("up"))){
            ptr = line + strlen("up") + 1;
            tmp = atoi(ptr);

            depth_1 -= tmp;
            aim -= tmp;
        
        }else{
            puts("WTFFFFFFF");
        }
    }

    fclose(fd);

    puts("------------- PART 1 -------------");
    printf("[x] Horizontal position : %d\n", horizontal);
    printf("[x] Depth : %d\n", depth_1);
    printf("[+] TOTAL : %d\n", depth_1 * horizontal);

    puts("\n------------- PART 2 -------------");
    printf("[x] Horizontal position : %d\n", horizontal);
    printf("[x] Depth : %d\n", depth_2);
    printf("[+] TOTAL : %d\n", depth_2 * horizontal);

    return EXIT_SUCCESS;
}