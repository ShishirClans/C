// input_output.c

/* This c file contains functions for handling input, output and summary of the calculation.   */

#include "header_file.h" // this is a user defined header file which has necessary function prototypes and the user defined constant. 

// using input function to read data from the given file 
int input(FILE* fptr, char* city, int* population, int* square_mileage, int* pollution_amount, int* crime, int* expense, int* number_of_highways) {
    //Reads different data about the city from te file and and returns it.
    return fscanf(fptr, "%s %d %d %d %d %d %d", city, population, square_mileage, pollution_amount, crime, expense, number_of_highways);
}

// Output function to  display information about the city 
void output(const char* city, double livability, double population_density) {
    // Print the city's name, livability, and population density using a specific formatted output. 
    printf("%-16s %11.2f %14.2f\n", city, livability, population_density);
}

// Summary function to display summary info
void summary(int number_of_cities, double total_livability, const char* best_city, double best_livability) {
    //Average livability value out of # number of cities is calculated.
    printf("\n\nOf %d cities, the average livability is %.2f \n", number_of_cities, total_livability / number_of_cities);
    // Most livabile city name with its livability value is displayed. 
    printf("The most livable city is %s with a livability of %.2f\n", best_city, best_livability);
}
