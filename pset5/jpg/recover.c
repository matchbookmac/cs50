/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Size of a block of memory
#define BLOCKSIZE 512

typedef uint32_t SIG;
typedef int8_t BYTE;

// struct for blocks of 512 bytes
typedef struct
{
    SIG sig;
    BYTE buffer[504];
    SIG end;
} __attribute__((__packed__))
BLOCK;

int main(int argc, char* argv[])
{
    // ensure correct usage
    if (argc != 1)
    {
        printf("Usage: ./recover.c\n");
        return 1;
    }

    // remember infile
    //char* infile = argv[1]; 

    // open infile
    FILE* inptr = fopen("card.raw", "r");
    
    // declare outfile
    FILE* outptr;

    // ensure valid file
    if (inptr == NULL)
    {
        printf("Could not open file \"card.raw\"\n");
        return 2;
    }
    
    // Boolean to tell if file is open
    int OPEN = 0;

    // buffer for jpg signatures
    BLOCK buff;

    // filename counter
    int c = 0;

    // string for filename
    char jpg[8]; 
    
    // start reading the file for signatures
    while (fread(&buff, sizeof(BYTE), BLOCKSIZE, inptr) == 512)
    {
        // if buffer has signature
        if (buff.sig == 0xe0ffd8ff || buff.sig == 0xffd8ffe1)
        {
            
            // determine new jpg file name
            sprintf(jpg, "%03d.jpg", c);

            // open new jpg file
            outptr = fopen(jpg, "w");
            
            // ensure valid file
            if (outptr == NULL)
            {
                printf("Could not open file \"%s\"\n", jpg);
                return 3;
            }
            
            // file is open
            OPEN = 1;

            // write buffer to file
            fwrite(&buff, sizeof(BYTE), BLOCKSIZE, outptr);
            
            // increment c
            c++;
        }
        
        // if the file is open, and there are bytes to read, continue writing
        while (OPEN == 1 && fread(&buff, sizeof(BYTE), BLOCKSIZE, inptr) == 512)
        {
            // if the next block starts a new file, close the current file
            if (buff.sig == 0xe0ffd8ff)
            {
                // close jpg file
                fclose(outptr);

                // file is closed
                OPEN = 0;

                // go back
                fseek(inptr, -BLOCKSIZE, SEEK_CUR);
            }        
            else
            {
                // write buffer to file
                fwrite(&buff, sizeof(BYTE), BLOCKSIZE, outptr);
            }
        }
    }

    // close input and output file
    fclose(inptr);
    fclose(outptr);

    return 0;
}
