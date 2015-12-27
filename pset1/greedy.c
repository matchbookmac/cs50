/*
 * greedy.c Ian C MacDonald 2014
 * pset1
 * CS50 via edX.org
 *
 * greedy.c provides the user with the number of coins to
 * return in change based on the amount of change provided
 * by the user.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cs50.h>
#include <math.h>
#include <stdio.h>


int main(void)
{
    
    // initializes variables used througout the code
    
    double f;
    long int cents = 0;
    long int quarters = 0;
    long int dimes = 0;
    long int nickels = 0;
    long int pennies = 0;
    int coins = 0;
    
    // gets an amount of change from the user
    
    do
    {
        printf("How much change is owed?: \n");
        f = GetFloat();
    }
    while (f < 0);
    
    // converts the float change value into a rounded number of cents
    
    cents = round(f * 100);
    
    // checks how many quarters will be used
    
    while (cents >= 25)
    {
        quarters = cents / 25;
        cents = cents % 25;
        coins = quarters;
    }
    
    // checks how many dimes
    
    while (cents >= 10)
    {
        dimes = cents / 10;
        cents = cents % 10;
        coins = quarters + dimes;
    }
    
    // checks how many nickels
    
    while (cents >= 5)
    {
        nickels = cents / 5;
        cents = cents % 5;
        coins = quarters + dimes + nickels;
    }
    
    // checks pennies
    
    while (cents >= 1)
    {
        pennies = cents / 1;
        cents = cents % 1;
        coins = quarters + dimes + nickels + pennies;
    }
    
    // returns number of coins needed
    
    printf ("%d\n", coins);
}
