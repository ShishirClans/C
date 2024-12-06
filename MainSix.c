/*
Programming Asssignment 6
Name - Shishir Ghorashainee
25th November, 2024
Professor Richard K Fox

Description :
This program finds the number that appears the most times in an array and prints it along with the count of its occurrences.
The logic is written in assembly, but the array and its size are defined in C.Two loops, an inner loop that counts how
many times that number occurs in the entire array and an outer loop to check each number in the array, are used in the program.
It compares the count of each number to the highest count.It stores the number and updates the maximum count if the current count is higher.
Four registers(eax, ebx, ecx, edx) are used to store values and also perform different operations like comparisons.At last, the result is stored
in maxNum and maxCount and as the loop ends, the program prints the number which appears to be the most and how many time it appears.

*/

#include <stdio.h>
int main() {
    //Variable Declarations
    /*
    int array[] = { 5,3,8,9,3,4,1,8,2,3,9,5,6,5,5,8,7,3,0,1,3,8,5,3,3,9,4,2,3,8,5,6,2,3,4,1,3,8,5 };  // Using given Array 2
    int n = 40; // Number of elements in the array
    */
    
    int array[] = { 25,26,27,28,29,30,25,26,27,29,30,25,28,30,27,30,26,27,28,25,24,26,27,26,27,26,28,26,30,25 };  // Using given Array 3
    int n = 30;   // Number of elements in the array   
    

    // To store the current number, its frequency (count), and the maximum number with its frequency count
    int number, count, maxNum = 0, maxCount = 0;

    __asm {
        mov ecx, 0              // Initialize outer loop counter to 0
        outer_loop:
            cmp ecx, n              // Compare current index with the total number of elements n
            jge outer_loop_end     // If ecx >= n, exit the outer loop
            mov eax, array[ecx * 4]        // Load the current number (array[ecx]) into eax
            mov number, eax       // Store the current number in the variable number
            mov edx, 0            // Initialize inner loop counter edx to 0
            mov ebx, 0            // Initialize count ebx to 0

        inner_loop:
            cmp edx, n            // Compare inner loop counter edx with the total number of elements n
            jge inner_loop_end      // If edx >= n, exit the inner loop
            mov eax, array[edx * 4] // Load the array into eax
            cmp eax, number        // Compare the current element with number
            jne skip_increment      // If the values are not equal, skip incrementing the count
            inc ebx                 // If the values are equal, increment the count in ebx 

       skip_increment:
            inc edx                 // Move to the next index in the inner loop
            jmp inner_loop          // Repeat the inner loop

         inner_loop_end:
            mov count, ebx          // Store the count of the current number into the count variable
            mov eax, maxCount       // Load maxCount into eax
            cmp ebx, eax            // Compare the current count ebx with maxCount
            jle skip_update        // If the current count is less than or equal to maxCount, then skip updating the maximum values
            mov eax, number        // Move the current number into eax
            mov maxNum, eax         // Store the current number in maxNum (to count the most repeated number)
            mov eax, count          // Move the current count into eax
            mov maxCount, eax       // Store the count in maxCount (to count the highest frequency)

       skip_update:
            inc ecx               // Increment the outer loop index stored in ecx
            jmp outer_loop          // Repeat the outer loop

       outer_loop_end:             // The Loop ends, then is ready to display the result
    }

    // Display the output 
    printf("%d occurs %d times\n", maxNum, maxCount);
    return 0;
}



/*
--------------------------------------------------------------------------------------------------------------------------------------------------
Array 2 (n=40): 5,3,8,9,3,4,1,8,2,3,9,5,6,5,5,8,7,3,0,1,3,8,5,3,3,9,4,2,3,8,5,6,2,3,4,1,3,8,5
Output using Array2:

3 occurs 10 times

-------------------------------------------------------------------------------------------------------------------------------------------------------
Array 3 (n=30): 25,26,27,28,29,30,25,26,27,29,30,25,28,30,27,30,26,27,28,25,24,26,27,26,27,26,28,26,30,25
Output using Array3:

26 occurs 7 times

*/