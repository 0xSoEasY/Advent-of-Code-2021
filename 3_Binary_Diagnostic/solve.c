// gcc -o solve solve.c -lm && ./solve input.txt
#include "solve.h"


/*
 - If OXYGEN_CHECK : get the most common bit at an offset
 - If CO2_CHECK : get the less common bit at an offset 
*/
char get_common_bit(bin_value bin_values[nb_lines], int offset, int check_type){
    int nb_1, nb_0;
    nb_1 = nb_0 = 0;

    for(int i=0; i < nb_lines; i++){
        if((bin_values[i].used_oxygen == USED && check_type == OXYGEN_CHECK) || (bin_values[i].used_co2 == USED && check_type == CO2_CHECK)){
            if(bin_values[i].value[offset] == '0'){
                nb_0++;
            }else{
                nb_1++;
            }
        }
    }

    // if equality
    if(nb_1 == nb_0){
        if(check_type == OXYGEN_CHECK){
            return '1';
        }else{
            return '0';
        }

    // if 1 most common
    }else if(nb_1 > nb_0){
        if(check_type == OXYGEN_CHECK){
            return '1';
        }else{
            return '0';
        }

    // if 0 most common
    }if(check_type == OXYGEN_CHECK){
        return '0';
    }else{
        return '1';
    }
}


/* Convert a binary string to an int */
int binary_str_to_int(char* bin_str){
    int result = 0;

    for(int i=0; i < INPUT_SIZE; i++){        
        if(bin_str[i] == '1'){
            result += (int) pow(2, strlen(bin_str) - 2 - i); // Don't ask, just trust me :D
        }
    }
    return result;
}


/* Print a int of INT_SIZE as binary */
void print_int_as_binary(int n, int offset) {
    for(int i=INT_SIZE-offset-1; i >= 0; i--){
        int k = n >> i;

        if (k & 1){
            printf("1");
        }else{
            printf("0");
        }
    }
}


/*
 Entry point
 */
int main(int argc, char** argv){

    FILE* fd;
    char line[128];
    char bit_criteria;
    int nb_1[INPUT_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int gamma, epsilon, oxygen, co2;

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


    nb_lines = gamma = epsilon = 0;
    // storing number of 1 at each offset in nb_1[]
    while(fgets(line, sizeof(line), fd)){
        nb_lines += 1;

        for(int i=0; i < INPUT_SIZE; i++){
            if(line[i] == '1'){
                nb_1[i] += 1;
            }
        }
    }

    // Convertion from binary (int[]) to decimal
    for(int i=0; i < INPUT_SIZE; i++){        
        if(nb_1[i] > (int)(nb_lines / 2) ){
            gamma += (int) pow(2, INPUT_SIZE - 1 - i);
        }
    }

    puts("-------------- PART 1 --------------");
    printf("[x] Gamma (%d) : ", gamma);
    print_int_as_binary(gamma, 20);

    // Flip bits, keeping the 12 last ones
    epsilon = ~gamma & 0x00000FFF;
    printf("\n[x] Epsilon (%d) : ", epsilon);
    print_int_as_binary(epsilon, 20);
    
    printf("\n[+] RESULT (gamma * epsilon) : %d\n", gamma * epsilon);


    //////////////////////////////////////////////////////////////////////
    /////////////////////////////   PART 2   /////////////////////////////
    //////////////////////////////////////////////////////////////////////


    puts("\n-------------- PART 2 --------------");
    // Putting fd back to the begining of the file
    fseek(fd, 0, SEEK_SET);
    bin_value bin_values[nb_lines];
    
    // Initilisation of bin_value structures
    for(int i=0; fgets(line, sizeof(line), fd); i++){
        strcpy(bin_values[i].value, line);
        bin_values[i].used_oxygen = USED;
        bin_values[i].used_co2 = USED;
    }

    fclose(fd);
    oxygen = co2 = 0;

    for(int i=0; i < INPUT_SIZE; i++){
        bit_criteria = get_common_bit(bin_values, i, OXYGEN_CHECK);

        // check oxygen values based on corresponding bit_criteria
        for(int j=0; j < nb_lines; j++){
            if(bin_values[j].value[i] != bit_criteria){
                bin_values[j].used_oxygen = NOT_USED;
            }
        }

        // check CO2 values based on corresponding bit_criteria
        bit_criteria = get_common_bit(bin_values, i, CO2_CHECK);
        for(int j=0; j < nb_lines; j++){
            if(bin_values[j].value[i] != bit_criteria){
                bin_values[j].used_co2 = NOT_USED;
            }
        }

        // convert binary string to int
        for(int j=0; j < nb_lines; j++){
            if(bin_values[j].used_oxygen == USED){
                oxygen = binary_str_to_int(bin_values[j].value);

            }if(bin_values[j].used_co2 == USED){
                co2 = binary_str_to_int(bin_values[j].value);
            }
        }
    }

    printf("[x] Oxygen (%d) : ", oxygen);
    print_int_as_binary(oxygen, 20);

    printf("\n[x] CO2 (%d) : ", co2);
    print_int_as_binary(co2, 20);

    printf("\n[+] RESULT (oxygen * CO2) : %d\n", oxygen * co2);

    return EXIT_SUCCESS;
}