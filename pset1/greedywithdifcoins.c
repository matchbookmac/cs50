#include <cs50.h>
#include <math.h>
#include <stdio.h>

// demonstrates floating point imprecision
int main(void)
{
    // gets a float from the user and then prints it
    
    double f;
    long int cents = 0;
    long int quarters = 0;
    long int dimes = 0;
    long int nickels = 0;
    long int pennies = 0;
    int coins = 0;
    
    do
    {
    printf("How much change is owed?: \n");
    f = GetFloat();
    }
    while (f < 0);
    
    cents = round(f * 100);
    //printf ("%ld \n", cents);
    
    while (cents >= 25)
    {
        quarters = cents / 25;
        cents = cents % 25;
        coins = quarters;
    }
    
    while (cents >= 10)
    {
        dimes = cents / 10;
        cents = cents % 10;
        coins = quarters + dimes;
    }
    
    while (cents >= 5)
    {
        nickels = cents / 5;
        cents = cents % 5;
        coins = quarters + dimes + nickels;
    }
    
    while (cents >= 1)
    {
        pennies = cents / 1;
        cents = cents % 1;
        coins = quarters + dimes + nickels + pennies;
    }
    
    //printf ("%ld \n", cents);
    //printf ("%ld \n", quarters);
    //printf ("%ld \n", dimes);
    //printf ("%ld \n", nickels);
    //printf ("%ld \n", pennies);
    printf ("%d\n", coins);
}
