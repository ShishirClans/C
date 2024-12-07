/*   Name: Shishir Ghorashainee
     Course: CSC 362
     Dr. Richard Fox
     Programming Assignment 1 
     Due Date:  6th September, 2024
     
     Description : This program reads characters from an input file provided by the user and processes every characters. If the character is a letter,
                   it shifts the letter forward in the alphabet by a rotation amount, which changes everytime a new letter is read 
                   or based on two special characters entered by the user. These characters inputs given by the user must be digits and/or punctuation marks.
                   The program resets the rotation (k) to 1 whenever it finds a space or a newline, and if the k exceeds 5, it resets k to 1.
                   At last, the program calculates and displays information like the number of letters processed, the total number of characters,
                   the average distance that the letters were changed, and the percentage of letters that was changed in the file. File pointers are used to read input file and write into the output file.

 */

#define _CRT_SECURE_NO_WARNINGS // We declare this to avoid a compiler warning that would cause the compiler to abandon its compilation
#include <stdio.h>
#include <ctype.h>              // functions like isalpha(), isupper() ...... are defined in this headerfile. 
void main()
{
    int k = 1;              // declaring the initial value for the rotation 
    char first, second;     // two user input characters for digits and/or punctuation marks 
    char inputFileName[50];
    char outputFileName[50];
    char currentCharacter;  // to access all the characters of the input file 
    char asciiValue;        // to store ASCII value of the letter. 

    FILE* fp1, * fp2;       // fp1 points to the input file, fp2 points to the output file

    int totalCharacters = 0;     // To store the total number characters read from the input file. 
    int lettersProcessed = 0;    // Total letters that are processed when the rotation occurs. 
    int distanceShift = 0;       // total distance the letters have been shifted

    printf("Enter the input file name: ");        // Get the input file name  
    scanf("%s", inputFileName);
    fp1 = fopen(inputFileName, "r");             // open input file, read-only

    if (fp1 == NULL)          // If the file does not exist then print some text.
    {
        printf("Not able to open the file!\n");
        return;
    }

    printf("Enter the output file name: ");        // Get the output file name.
    scanf("%s", outputFileName); 
    fp2 = fopen(outputFileName, "w");              // open output file, write-only.
   
    do        // Prompt two character input to the user and check if they are either digit and/or punctuation
    {
        printf("Enter the chars that will increment k, they must be digits and/or punctuation marks ");
        scanf(" %c %c", &first, &second);
    } while (!((isdigit(first) || ispunct(first)) && (isdigit(second) || ispunct(second))));  

    while ((currentCharacter = getc(fp1)) != EOF)  // get next char from the input file, store in currentCharacter, until it reaches EOF 
    {
        totalCharacters++;     // this counts the total number of characters read.

        if (k > 5) {
            k = 1;             // Reset k if it's greater than 5
        }
        if (isalpha(currentCharacter))   // Check if a character is an alphabetic or not
        {
            asciiValue = isupper(currentCharacter) ? 'A' : 'a';      // Determine if it's uppercase or lowercase, then store the ASCII value accordingly.
            currentCharacter = (char)(currentCharacter + k);         // shift the letter to a letter by k away 

            if (currentCharacter > asciiValue + 25)   // Check if ASCII of current character is beyond 'Z' or 'z' and substract 26 to make it a letter.
            {
                currentCharacter -= 26;          
            }

            lettersProcessed++;    // Count the number of letters that were actually processed
            distanceShift += k;    // Increment total distance shifted by the current k value

            k++;                   // Increment k for the next letter
            
        }
        else     //if the currentCharacter is not an alphabet then proceed to this part. 
        {
            if (currentCharacter == ' ' || currentCharacter == '\t' || currentCharacter == '\n') // If char is blank, tab or new line then reset k
            {
                k = 1; 
            }
            if (currentCharacter == first || currentCharacter == second)          // Increment k if it matches one of the character entered by the user.
            {
                k++; 
            }
        }
        putc(currentCharacter, fp2);              // Write the processed letters into the output file
    }
    fclose(fp1);          // Closing both files.
    fclose(fp2);

    double percentageLetters = ((double)lettersProcessed / totalCharacters) * 100 ; // Calculate percentage change in the Input file after encrypting.
    double averageDistance = (double)distanceShift / lettersProcessed;              // Calculate the average distance shifted.

    // Display all of the calculations performed 
    printf("Input File:\t \t%s\n", inputFileName);
    printf("Output File:\t \t%s\n", outputFileName);
    printf("Letters processed:\t%d\n", lettersProcessed);
    printf("Total characters:\t%d\n", totalCharacters);
    printf("Average distance:\t%.3f\n", averageDistance);
    printf("Percentage letters:\t%.3f%%\n", percentageLetters);
}



/************************************************************************************/

/*
    // for the 1st Input File 

Input:
Enter the input file name input1.txt
Enter the output file name output1.txt
Enter the chars that will increment k, they must be digits and/or
punctuation marks , -


Output:
Input File:             input1.txt
Output File:            output1.txt
Letters processed:      120
Total characters:       157
Average distance:       2.483
Percentage letters:     76.433%

Created text file (output1.txt):
Jpiswncwmto ju oqw lpraqffji;
lpraqffji ju oqw xkvhtn,
xkvhtn ju oqw utxxm,
utxxm -- ju oqw cgdyyz,
cgdyyz ju oqw mqyi,
mqyi ju oqw nwvmh.
NWVMH ju ujh CGVX!

*/



// for the 2nd Input file

/*  
Input:
Enter the input file name : input2.txt
Enter the output file name : output2.txt
Enter the chars that will increment k, they must be digits and/or
punctuation marks 1 .

Output: 
Input File:             input2.txt
Output File:            output2.txt
Letters processed:      559
Total characters:       728
Average distance:       2.606
Percentage letters:     76.786%

Created text file (output2.txt):

Bdgyhukrr ju egimsff bu "jpiiwfpfi uq ujh cgvx fzspfocwmto,"
b ucvo ph hgqiwbvlrl bp fzspfocwmto uq befszov gqu ujh
brsifscqgj ph b hkyis tgw ph gkqhnoiv pt ecwe [8].  Xkwlno
ujh dqqxjyv ph icqhbskwxjo djdvfdvhv sgfslokwmto, ujh ucvo
ju pph ph iassyigvmejpj ujh djdvfdvhvx (pt tapftmu/zsweu)
sgvttoulfqf gqu ujh ggdxzsgv gqxri jp tedrsff ckwqfqu;
ujh ucvo bvwirqvv uq gkqh ujh cgvx dqopjdvlss ph djdvfdvhvx uq
fzspfjp ujhwj ggdxzsgv.  Bdgyhukrr icv qthznpwvpd cghr
brspnff uq b xkgi scqkj ph jpwiwqthxfukrr qtrfqfov jpfpzekqk
trhihi sgfslokwmto [9], ekdkspulw [10, 11, 12], nggmhbn ugvx
jpwiwqthxfukrr [13], tvrvd vpgiwtvdrijpj [14], ocwywbn
mcqkzbih vpgiwtvdrijpj [9, 15], ujhswz gquqfukrr bpg mgjeq
sgdwtokqk [16].


*/



/************************************************************************************/
