// header_file.h
/*This header file contains header files like stdio.h, string.h needed for other c files as well as the function prototypes */

#define _CRT_SECURE_NO_WARNINGS  // We declare this to avoid a compiler warning that would cause the compiler to abandon its compilation
#include <stdio.h>
#include <string.h>  //Various string functions like strcpy is defined in this headerfile. 

//Declaring CONSTANTS for different calculations. 
#define POLLUTION_CONSTANT 1112.2
#define TRAFFIC_CONSTANT 1.7
#define CRIME_CONSTANT 872.6
#define EXPENSE_CONSTANT 1617.1
#define LIVABILITY_CONSTANT 13.81

// All the given function prototypes

// Reads city data using pointer to point (city_name, population, square_mileage, pollution_amount, crime, expenses, number of highways) from a file.
int input(FILE* fptr, char* city, int* population, int* square_mileage, int* pollution_amount, int* crime, int* expense, int* number_of_highways);

// Calculate the population density by dividing city population by area in square miles. 
double population_density(int population, int square_mileage);

// Computes pollution amount, traffic, crime, and expense ratings for a city based on input data. And the parameters with pointers are passed by using their address. 
void compute(int pollution_amount, int crime, int expense, int number_of_highways, double population_density, double* pollution_rating, double* traffic_rating, double* crime_rating, double* expense_rating);

// this function calculates the overall livability value for a city by combining all the ratings and substracts it from 100.
double livability(double pollution_rating, double traffic_rating, double crime_rating, double expense_rating);

// this output function displays the city’s name, livability value, and population density in a formatted way.
void output(char* city, double livability, double population_density);

// Updates totals for number of cities, total livability. Also, the best city and its livability are recorded. 
void update(int* number_of_cities, double* total_livability, char* best_city, double* best_livability, char* city, double city_livability);

//summary function gives us a report for the number of cities, its livability value and the name of the most livable city.
void summary(int number_of_cities, double total_livability, char* best_city, double best_livability);

