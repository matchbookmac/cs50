/*
 * caesar.c Ian C. MacDonald 030214
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Takes a single command line argument from the user,
 * "key," which must be an int. caesar.c then uses the
 * key to then encypher any text provided by the user.
 * Capitalization is maintained, numbers and other chars
 * are ignored. The encyphered text is printed at the 
 * command line.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */


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
        printf("Caesar arguments: ");

        for (int i = 2; i < argc; i++)
        {
            printf("\"%s\" ", argv[i]);
        }

        printf("not valid.\n");

        return 1 ;
    }

    // converts the user's command line argument into an int

    int key = atoi(argv[1]);

    /* checks to see if the user's input was an int by seeing if the
     output of atoi() was = 0 */

    if (key == 0)
    {
        printf("Caesar key: \"%s\" was not an int greater than 0.\n", argv[1]);
        return 1;
    }

    // gets text to encode from user

    string msg = GetString();

    // encyphers the user's string and prints it out

    for (int i = 0, n = strlen(msg); i < n; i++)
    {
        int txt = msg[i];
        
        if ((txt >= 'A' && txt <= 'Z') || (txt >= 'a' && txt <= 'z'))
        {
            if (isupper(txt))
            {
                int alph = txt - 64;
                int asc = (alph + key) % 26;
                int car = asc + 64;
                printf("%c", car);
            }
            else
            {
                int alph = txt - 96;
                int asc = (alph + key) % 26;
                int car = asc + 96;
                printf("%c", car);
            }
        }
        else
        {
            printf("%c", txt);
        }
    }
    printf("\n");
}
