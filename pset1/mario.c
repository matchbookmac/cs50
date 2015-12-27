/*
 * mario.c Ian C MacDonald 2014
 * pset1
 * CS50 via edX.org
 * 
 * mario.c creates a mario pyramid of a height provided by the user.
 *
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int input;
    
    // Gets height of pyramid from user
    
    do
    {
        printf("Height:");
        input = GetInt();
    }
    while (input > 23 || input < 0);
    
    // Loop for printing whole pyramid
    
    for (int i = 0, j = (input - i - 1), k = i; i < input; i++)
    {
        
        // Loop for printing spaces before sharps
        
        while (j < (input + 1) && j > 0)
        {
            printf(" ");
            j--;
        }
        
        j = (input - i - 2);
        
        // Loop for printing sharps after spaces
        
        printf("#");
        
        do
        {
            printf("#");
            k--;
        }
        while(k > 0);
        
        k = (i + 2);
        
        printf("\n");
    }
}
