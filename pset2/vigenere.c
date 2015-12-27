/*
 * caesar.c Ian C. MacDonald 030514
 * pset2
 * CS50 via edX.org
 *
 * Takes a single command line argument from the user,
 * "key," which must be an int. caesar.c then uses the
 * key to then encypher any text provided by the user.
 * Capitalization is maintained, numbers and other chars
 * are ignored. The encyphered text is printed at the 
 * command line.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    /* checks to make sure the user has only provided one command line
     argument. If they have not, it provides which arguments were
     extraneous. */

    if (argc > 2 || argc < 2)
    {   
        printf("Vigenere arguments: ");

        for (int i = 2; i < argc; i++)
        {
            printf("\"%s\" ", argv[i]);
        }

        printf("not valid.\n");

        return 1;
    }
    
    // checks to make sure that the command line argument is only letters

    string key = argv[1];

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if ((key[i] < 'A' || key[i] > 'Z') && (key[i] < 'a' || key[i] > 'z') )
        {
            printf("\"%s\" is not a valid key.\n", key);
            return 1; 
        }
    }

    // gets text to encode from user
    
    string msg = GetString();

    // encyphers the user's string and prints it out
    /* I don't think that nested loops will work, try using two variables
       incrementing one for the key and one for the text. if part of the text
       is not a letter, decriment the key variable and move on */
    
    for (int i = 0, j = 0, n = strlen(msg), kln = strlen(key) - 1; i < n; i++, j++)
    {
        if (j == kln + 1)
        {
            j = 0;
        }

        int txt = msg[i];
        int pin = key[j];
        
        if (pin >= 'A' && pin <= 'Z')
        {
            pin = pin - 65;
        }
        if (pin >= 'a' && pin <= 'z')
        {
            pin = pin - 97;
        }
        
        if ((txt >= 'A' && txt <= 'Z') || (txt >= 'a' && txt <= 'z'))
        {
            if (isupper(txt))
            {
                int alph = txt - 65;
                int asc = (alph + pin) % 26;
                int car = asc + 65;
                printf("%c", car);
            }
            else
            {    
                int alph = txt - 97;
                int asc = (alph + pin) % 26;
                int car = asc + 97;
                printf("%c", car);
            }
        }
        else
        {
            printf("%c", txt);
            j--;
        }
    }
    printf("\n");
}
