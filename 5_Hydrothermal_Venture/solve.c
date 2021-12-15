#include "solve.h"

/*
 Print a diagram (WARNING: a 1000x1000 diagram is way to much to be printed)
 --> Used for debug mode on the "test_input.txt" file
 */
void print_diagram(int diagram[DIAG_MAX_SIZE][DIAG_MAX_SIZE]){
    for(int y=0; y < DIAG_MAX_SIZE; y++){
        for(int x=0; x < DIAG_MAX_SIZE; x++){
            if(diagram[y][x] == 0){
                printf(". ");
            }else{
                printf("%d ", diagram[y][x]);
            }
        }
        puts("");
    }
}


/* Draw an horizontal line for a y value in a diagram */
void draw_horizontal_line(int diagram[DIAG_MAX_SIZE][DIAG_MAX_SIZE], coords* coords){
    int x_min = MIN(coords->x1, coords->x2);
    int x_max = MAX(coords->x1, coords->x2);

    for(int i = x_min; i <= x_max; i++){
        diagram[coords->y1][i]++;
    }
}


/* Draw a vertical line for a x value in a diagram */
void draw_vertical_line(int diagram[DIAG_MAX_SIZE][DIAG_MAX_SIZE], coords* coords){
    int y_min = MIN(coords->y1, coords->y2);
    int y_max = MAX(coords->y1, coords->y2);

    for(int i = y_min; i <= y_max; i++){
        diagram[i][coords->x1]++;
    }
}


/* Draw an diagonal line in a diagram */
void draw_diagonal_line(int diagram[DIAG_MAX_SIZE][DIAG_MAX_SIZE], coords* coords){
    int steps = abs(coords->x2 - coords->x1) + 1;

    for(int i=0; i < steps; i++){
        diagram[coords->y1][coords->x1]++;
        coords->y1 += coords->y2 - coords->y1 >= 0 ? 1 : -1;
        coords->x1 += coords->x2 - coords->x1 >= 0 ? 1 : -1;
    }
}


/* Get the score : number of points >= 2 */
int get_score(int diagram[DIAG_MAX_SIZE][DIAG_MAX_SIZE]){
    int score = 0;

    for(int y=0; y < DIAG_MAX_SIZE; y++){
        for(int x=0; x < DIAG_MAX_SIZE; x++){
            if(diagram[y][x] > 1){
               score++;
            }
        }
    }
    return score;
}


/*
 Entry point of the program
 */
int main(int argc, char** argv){

    FILE* fd;
    char line[128];
    int diagram[DIAG_MAX_SIZE][DIAG_MAX_SIZE];
    coords* coords = malloc(sizeof(coords));

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


    // Initialisation of the grid (0 in every case)
    for(int y=0; y < DIAG_MAX_SIZE; y++){
        for(int x=0; x < DIAG_MAX_SIZE; x++){
            diagram[y][x] = 0;
        }
    }

    while(fgets(line, sizeof(line), fd)){
        sscanf(line, "%d,%d -> %d,%d", &coords->x1, &coords->y1, &coords->x2, &coords->y2);

        if(coords->x1 == coords->x2){
            draw_vertical_line(diagram, coords);

        }else if(coords->y1 == coords->y2){
            draw_horizontal_line(diagram, coords);
        }
    }

    #ifdef DEBUG
        print_diagram(diagram);
        puts("------------------------");
    #endif
    printf("[+] Score (part. 1) : %d\n", get_score(diagram));


    //////////////////////////////////////////////////////////////////////
    /////////////////////////////   PART 2   /////////////////////////////
    //////////////////////////////////////////////////////////////////////


    // Initialisation of the grid (0 in every case)
    for(int y=0; y < DIAG_MAX_SIZE; y++){
        for(int x=0; x < DIAG_MAX_SIZE; x++){
            diagram[y][x] = 0;
        }
    }

    // Go back to the first line
    fseek(fd, 0, SEEK_SET);

    while(fgets(line, sizeof(line), fd)){
        sscanf(line, "%d,%d -> %d,%d", &coords->x1, &coords->y1, &coords->x2, &coords->y2);

        if(coords->x1 == coords->x2){
            draw_vertical_line(diagram, coords);

        }else if(coords->y1 == coords->y2){
            draw_horizontal_line(diagram, coords);
        
        }else{
            draw_diagonal_line(diagram, coords);
        }
    }

    #ifdef DEBUG
        puts("------------------------");
        print_diagram(diagram);
        puts("------------------------");
    #endif
    
    printf("[+] Score (part. 2) : %d\n", get_score(diagram));

    return EXIT_SUCCESS;
}