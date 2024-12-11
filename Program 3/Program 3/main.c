/*
 Name: Shishir Ghorashainee
 Programming Assignment 3
 Professor Richard Fox

 Description: This program sorts an array of integers using two different sorting algorithms,they are Bubble Sort and Selection Sort. It begins with an array called array1, having unsorted numbers.
     First, it makes a copy of array1 into a second array, array2, so that each sort algorithm operates on the origina data that is unsorted.Then, Bubble Sort is applied to array1, and 
     Selection Sort is applied to array2. Both sorting functions access array elements using pointers rather than standard indexing. After sorting, the program displays each sorted array,
     again using pointers to access and print the elements.

*/

#define _CRT_SECURE_NO_WARNINGS  // We declare this to avoid a compiler warning that would cause the compiler to abandon its compilation
#include <stdio.h>

// Function prototypes
void copy(int* src, int* dest, int size);
void sort1(int* array, int size);
void sort2(int* array, int size);
void output(int* array, int size);

void main() {
    //Variable Declarations 
    int array1[] = { 10, 3, 6, 5, 9, 2, 1, 7, 4, 8 }; // initializing array1 (Given Array) with random numbers from 1 to 10.
    //int array1[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // to Test it after the 1st output
    int array2[10]; // Declaring the 2nd array to receive the copied contents from array1. 
    int size = 10;  // This holds the size of arrays
    copy(array1, array2, size); // Copies the contents of array1 to array2 until all the size of the elements are copied. 
    sort1(array1, size); // Sort array1 using the Bubble Sort
    printf("array1 using Bubble Sorting:    ");
    output(array1, size); // Outputs the sorted array1
    sort2(array2, size); // Sort array2 using the Selection Sort
    printf("array2 using Selection sorting: ");
    output(array2, size); // Outputs the sorted array2 using the same output function at the end. 
}

// Elements of the array copied from source to destination using pointers
void copy(int* src, int* dest, int size) {
    for (int* p = src, *q = dest; p < src + size; p++, q++) {     // p loops through src, and q through dest
        *q = *p;         // Copies value from src array to dest array
    }
}

// Sorts an array using Bubble Sort algorithm
void sort1(int* array, int size) {              // Takes an integer array and its size as parameters to sort the array in ascending order using Bubble sorting.
    int sorted = 0;// To indicate if the array is Not Sorted(0) or Sorted(1). 
    int k = size;    // Initialize k to the size of the array
    while (!sorted) {                           // Loop until the array's been sorted
       sorted = 1;                             // Assuming that the array is sorted
        for (int* p = array; p < array + k - 1; p++) { // Loop through the array elements
            if (*p > *(p + 1)) {                // If current element is greater than the next
                sorted = 0;             // To indicate the array isn't fully sorted
                int temp = *p;                  // Swap the elements
                *p = *(p + 1);
                *(p + 1) = temp;
            }
        }
        k--;             // Reduce the k once the last element is sorted.
    }
}

// Sorts an array using Selection Sort algorithm
void sort2(int* array, int size) {     // Takes an integer array and its size as parameters to sort the array in ascending order using Selection sorting.
    for (int* p = array; p < array + size - 1; p++) { // Looping over an array to find the minimum value
        int* minPosition = p;              // Assuming that the current position is minimum
        for (int* q = p + 1; q < array + size; q++) { // To find the smallest element in the unsorted data
            if (*q < *minPosition) {       // If current element is smaller than minPosition element,
                minPosition = q;           // then update the minPosition
            }
        }
        int temp = *minPosition;          // Swap the smallest element found in the unsorted array with the current element
        *minPosition = *p;
        *p = temp;
    }
}

// Output function using the pointers
// After the Bubble Sort is applied to array1, the output function is called
// to print array1 that is sorted. Similarly, after the Selection Sort is applied
// to array2, the output function is called again to print array2 that is sorted.
void output(int* array, int size) {
    for (int* p = array; p < array + size; p++) {       // Loops through the array with the help of pointers
        printf("%d ", *p);   // Print each element value
    }
    printf("\n");  
}




/*

When we use array1[] = { 10, 3, 6, 5, 9, 2, 1, 7, 4, 8 }, the output is: 

array1 using Bubble Sorting:    1 2 3 4 5 6 7 8 9 10
array2 using Selection sorting: 1 2 3 4 5 6 7 8 9 10


---------------------------------------------------------------------------------------------------------------------


 When we use array1[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 },  The output is: 
 
array1 using Bubble Sorting:    1 2 3 4 5 6 7 8 9 10
array2 using Selection sorting: 1 2 3 4 5 6 7 8 9 10

*/