#include "solve.h"


/* Print the informations of a bingo_grid */
void print_grid(bingo_grid bingo_grid){
    puts("=================== GRID ===================");
    for(int y=0; y < GRID_SIZE; y++){
        for(int x=0; x < GRID_SIZE; x++){
            printf("\t%d", bingo_grid.grid[y][x]);
        }
        puts("");
    }

    puts("================== MARKED ==================");
    for(int y=0; y < GRID_SIZE; y++){
        for(int x=0; x < GRID_SIZE; x++){
            printf("\t%d", bingo_grid.marked[y][x]);
        }
        puts("");
    }
    printf("---> Has won : %d\n\n", bingo_grid.has_won);
}


/* Convert a str to a int array using a delimiter */
void str_to_int_array(const char* delim, char* string, int* array){
    char* ptr = strtok(string, delim);

	for(int i=0; ptr != NULL; i++){
        array[i] = atoi(ptr);
        ptr = strtok(NULL, delim);
    }
}


/* In a bingo_grid, mark the values corresponding to the draw */
void mark_value_in_grid(bingo_grid* bingo_grid, int draw){
    for(int y=0; y < GRID_SIZE; y++){
        for(int x=0; x < GRID_SIZE; x++){

            if(bingo_grid->grid[y][x] == draw){
                bingo_grid->marked[y][x] = MARKED;
            }
        }
    }
}


/* Return MARKED if at least a full list or column is marked, UNMARKED else */
int check_has_won(bingo_grid bingo_grid){
    int nb_marked_per_column;
    int nb_marked_per_line;

    for(int x=0; x < GRID_SIZE; x++){
        nb_marked_per_column = 0;
        nb_marked_per_line = 0;

        for(int y=0; y < GRID_SIZE; y++){
            if(bingo_grid.marked[y][x] == MARKED){
                nb_marked_per_column++;

            }if(bingo_grid.marked[x][y] == MARKED){
                nb_marked_per_line++;
            
            }if(nb_marked_per_column == GRID_SIZE || nb_marked_per_line == GRID_SIZE){
                return MARKED;
            }
        }
    }
    return UNMARKED;
}


/* Get the number of values separated by a "," */
int get_nb_values(char* line, char delim){
    char* ptr = line;
    int nb_values;
    
    for(nb_values=0; ptr[nb_values]; ptr[nb_values]==delim ? nb_values++ : *ptr++);

    return nb_values + 1;
}


/* Calulate the score : (sum of all UNMARKED) * last_draw */
int get_score(bingo_grid bingo_grid, int last_draw){
    int sum_unmarked = 0;

    for(int y=0; y < GRID_SIZE; y++){
        for(int x=0; x < GRID_SIZE; x++){
            if(bingo_grid.marked[y][x] == UNMARKED){
                sum_unmarked += bingo_grid.grid[y][x];
            }
        }
    }

    return sum_unmarked * last_draw;
}




/*
Entry point of the program
*/
int main(int argc, char** argv){

    FILE* fd;
    char line[300];
    int tmp_line[GRID_SIZE];
    int score1, score2, nb_values, nb_grids, nb_lines, first_winning_grid_index, last_winning_grid_index;

    if(argc < 2){
        printf("\tUsage : %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = fopen(argv[1], "r");

    if(fd == NULL){
        printf("[-] Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    fgets(line, sizeof(line), fd);
    printf("[x] Data set : %s", line);

    // Counting how many numbers are in the dataset by counting ","
    nb_values = get_nb_values(line, ',');
    printf("[x] Number of values : %d\n", nb_values);

    // Declaring a int tab to store all the values of the dataset as int
    int dataset[nb_values];
    str_to_int_array(",", line, dataset);

    nb_grids = nb_lines = 0;
    while(fgets(line, sizeof(line), fd)){
        nb_lines++;
    }

    nb_grids = nb_lines / 6; // 5 lines + 1 empty line per grid
    printf("[x] Number of grids : %d\n", nb_grids);

    bingo_grid* bingo_grids = (bingo_grid*) malloc(nb_grids * sizeof(bingo_grid));

    fseek(fd, 0, SEEK_SET);
    fgets(line, sizeof(line), fd); // skipping first line (dataset)

    for(int i=0; i < nb_lines; i += 6){
        // skipping empty line
        fgets(line, sizeof(line), fd);
        
        for(int j=0; j < GRID_SIZE; j++){
            // 1 grid == 6 lines
            int grid_index = (int) i / 6;
            fgets(line, sizeof(line), fd);
            str_to_int_array(" ", line, tmp_line);

            for(int k=0; k < GRID_SIZE; k++){
                bingo_grids[grid_index].grid[j][k] = tmp_line[k];
                bingo_grids[grid_index].marked[j][k] = UNMARKED;
            }

            bingo_grids[grid_index].has_won = UNMARKED;
        }
    }

    fclose(fd);

    int check_result = 0;
    first_winning_grid_index = -1;

    for(int i=0; i < nb_values; i++){
        for(int j=0; j < nb_grids; j++){
            if(bingo_grids[j].has_won == UNMARKED){
            
                mark_value_in_grid(&bingo_grids[j], dataset[i]);
                check_result = check_has_won(bingo_grids[j]);
                
                if(check_result != UNMARKED){
                    // If this is the first grid to win
                    if(first_winning_grid_index == -1){
                        first_winning_grid_index = j;
                        score1 = get_score(bingo_grids[first_winning_grid_index], dataset[i]);
                    }
                    // Calculate the score for the next winners until the last one
                    last_winning_grid_index = j;
                    score2 = get_score(bingo_grids[last_winning_grid_index], dataset[i]);

                    bingo_grids[last_winning_grid_index].has_won = MARKED;
                }
            }
        }
    }

    // Display the results
    printf("[x] First grid to win is the n°%d\n", first_winning_grid_index);
    print_grid(bingo_grids[first_winning_grid_index]);

    printf("[x] Last grid to win is the n°%d\n", last_winning_grid_index);
    print_grid(bingo_grids[last_winning_grid_index]);

    printf("[+] Score (part. 1) : %d\n", score1);
    printf("[+] Score (part. 2) : %d\n", score2);

    // Useless here but good habit to have :D
    free(bingo_grids);
    bingo_grids = NULL;

    return EXIT_SUCCESS;
}