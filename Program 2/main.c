/*
Name - Shishir Ghorashainee
Programming Assignment 2 

Prof. Richard K. Fox
*/

/*
    This program reads city data from a file and calculates various data, such as population density, pollution, traffic, crime, expense,
    number of highways.Using these data, it computes a livability value for each city and displays the results. It also keeps track of 
    the best or most livable city and provides a summary of all cities, including the average livability and the name of the best city.

    In the main.c file we have declared the necessary variables needed, used a file pointer to open and read a file, an output format
    for the heading, once the the file is closed once its read and summary function is called which gives us a report for the number of cities, its livability value and the name of the most livable city.
  
*/


// main.c
#include "header_file.h" // this is a user defined header file which has necessary function prototypes and the user defined constants. 

int main() {
    // Declaring all the variables needed. 
    char city[60], best_city[60];   // These char variables store the name of cities and the best city. 
    int population=0, square_mileage=0, pollution_amount=0, crime=0, expense=0, highways=0, number_of_cities=0; //These int variables store the city population, area in sq. miles, pollution, number of crime, expenses, the number of major highways, and the number of cities. 
    double total_livability = 0, best_livability = 0, city_livability = 0; // This holds the value for total_livability, best livability, and current city livability. 
    double pop_density = 0;   // To store the density of poplation value after being called inside a function. 
    double pollution_rating=0, traffic_rating=0, crime_rating=0, expense_rating=0;  // To hold values after they're calculated. 

    // Opening the input file. 
    FILE* fptr = fopen("cities2.txt", "r"); //opening the file in Read only mode 
    if (fptr == NULL) {    // Gives an error message if the file doesn't exist.
        printf("Error opening file.\n");
        return 1;
    }

    printf("City                 Livability   Pop Density\n");    // Creating the headings for the output with a proper format.


    // Using While loop, we loop through each city from the given input file. 
    while (input(fptr, city, &population, &square_mileage, &pollution_amount, &crime, &expense, &highways) != EOF) { 
        pop_density = population_density(population, square_mileage); // Population density is computed

        //We compute various ratings based on what factors a city has. 
        compute(pollution_amount, crime, expense, highways, pop_density, &pollution_rating, &traffic_rating, &crime_rating, &expense_rating);

        //We calculate the city livavility value. 
        city_livability = livability(pollution_rating, traffic_rating, crime_rating, expense_rating);

        //output results for the current city name, livilability score, and population density. 
        output(city, city_livability, pop_density);

        ////In this, we update the number of cities, total livability, and also we check if the current city has the best livability. 
        update(&number_of_cities, &total_livability, best_city, &best_livability, city, city_livability);
    }

    fclose(fptr);  // Close the input file

    // Outputs the number of cities, total_livability, best city and best livability. And, the Average livabilty is also displayed.
    summary(number_of_cities, total_livability, best_city, best_livability);

    return 0;
}

/*

//Output for Cities2.txt 


City                 Livability   Pop Density
Atlanta                40.54         752.98
Boston                 23.63        1022.35
Chicago                17.94         935.06
Cincinnati             71.77         449.88
Dallas                 53.11         714.73
Houston                50.50         706.82
Las_Vegas              47.95         817.78
Los_Angeles             4.58        1134.00
Minneapolis            73.19         404.78
New_York_City           4.76        1096.80
Seattle                55.27         650.97
St_Louis               75.83         332.31
Washington_DC          24.02         921.97


Of 13 cities, the average livability is 41.78
The most livable city is St_Louis with a livability of 75.83

*/