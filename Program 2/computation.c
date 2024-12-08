// computation.c

/*
    The 'computation.c' file contains functions that perform calculations related to city livability.
    It includes functions to calculate population density, different ratings like pollution, traffic, crime, and expense. Also, the total livability is calculated. .
    We can determine how livable each city is based on the input data.
*/


#include "header_file.h" // this is a user defined header file which has necessary function prototypes and the user defined constant. 

// Compute population density using the function 
double population_density(int population, int square_mileage) {
    return (double)population / square_mileage;     // we divide the city population by its area and return the value. 
}

// Funtion to calculate various ratings like pollution, traffic, crime, and expense rating respectively using the given formula. 
void compute(int pollution_amount, int crime, int expense, int number_of_highways, double population_density, double* pollution_rating, double* traffic_rating, double* crime_rating, double* expense_rating) {
    *pollution_rating = (pollution_amount * population_density) / POLLUTION_CONSTANT;
    *traffic_rating = (population_density * TRAFFIC_CONSTANT) / number_of_highways;
    *crime_rating = (crime * population_density) / CRIME_CONSTANT;
    *expense_rating = (expense * population_density) / EXPENSE_CONSTANT;
}

// Function to calculate livability value using the given formula and dividing by user defined constant. 
double livability(double pollution_rating, double traffic_rating, double crime_rating, double expense_rating) {
    //Based on the formula this function calculates the livability value and returns the livability value as double.  
    return 100 - (pollution_rating + traffic_rating + crime_rating + expense_rating) / LIVABILITY_CONSTANT;
}

// Update function to track livability data using strcpy
void update(int* number_of_cities, double* total_livability, char* best_city, double* best_livability, char* city, double city_livability) {
    (*number_of_cities)++;  // Increasing the number of cities
    *total_livability += city_livability;  // Change the total livability value. 
    //If condition to check if the current city livability is greater than the best livability city.
    if (city_livability > *best_livability) {     
        *best_livability = city_livability;   //if the condition holds true, then we update the best livability city. 
        strcpy(best_city, city);  // We copy the contents from the current city name and put it into best city.
    }
}
