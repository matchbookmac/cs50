/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * resizes an inputfile.bmp by a factor of n into an outputfile.bmp
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // set factor
    double f = atof(argv[1]);

    // check to make sure user provided a real number 
    if (f == 0)
    {
        printf("Please provide an int for \"n\"\n");
        return 2;
    }

    // ensure n factor greater than 1 or less than 100
    if (f < 1.0 || f > 100.0)
    {
        printf("Resize factor, n, is not an int > 1 or < 100\n");
        return 3;
    }

    // cast float f to an int factor
    int factor = (int) f;

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 5;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 6;
    }

    // determine padding for input scanlines
    int inpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // original height and width
    int inwidth = bi.biWidth;
    int inheight = bi.biHeight;

    // determine height and width for file infoheader
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;
    
    // determine padding for scanlines
    int outpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine file size for header and infoheader
    bi.biSizeImage = (bi.biWidth * 3 + outpadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inheight); i < biHeight; i++)
    {
        // temp storage for the scanline
        RGBTRIPLE scanline[inwidth][factor]; 

        // iterate over pixels in scanline
        for (int k = 0; k < inwidth; k++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // as many times as the file is being expanded
            for (int l = 0; l < factor; l++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                scanline[k][l] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, inpadding, SEEK_CUR);

        // then add appropriate amount of padding for new file size 
        for (int m = 0; m < outpadding; m++)
        {
            fputc(0x00, outptr);
        }

        // rewrite the copied scanline to the outfile
        for (int o = 1; o < factor; o++)
        {
            // copy the scanline to the file
            fwrite(&scanline, sizeof(scanline), 1, outptr);
            
            // write in the padding
            for (int p = 0; p < outpadding; p++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
