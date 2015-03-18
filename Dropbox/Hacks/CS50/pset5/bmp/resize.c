/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP image by the factor of n. (n>1)
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scaleFactor infile outfile\n");
        return 1;
    }
    // ensures scale factor >= 1
    if (atoi(argv[1]) < 1)
    {
    	printf("Scale factor must be greater than or equal to 1");
    }

    // remember filenames and scale factor
    int scaleFactor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
   
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }    
    // make changes to header file dimensions
    int original_height = bi.biHeight;
    int original_width = bi.biWidth;
    
    bi.biHeight = bi.biHeight * scaleFactor; 
    bi.biWidth = bi.biWidth * scaleFactor; 
    
    // determine padding for scanlines of out file and infile
    int padding = (4 - (original_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // make changes to header file sizes
    bi.biSizeImage = ((bi.biWidth) * sizeof(RGBTRIPLE) + (new_padding)) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // initialize counter and rewind factor.
    int counter = 0;
    int rewind =   - (original_width * sizeof(RGBTRIPLE) + padding); 
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(original_height); i < biHeight; i++)
    {
        // repeating the horizontal resize n times to get the vertical resize.
        while (counter < scaleFactor)
        {   
            // iterate over pixels in scanline
            for (int j = 0; j < original_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int m = 0; m < scaleFactor; m++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }                            
            }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }         
            // increment counter 
            counter++;   
                        
            // rewind the pointer to the start of the scanline
            if (counter < scaleFactor)
            {
            	fseek(inptr, rewind, SEEK_CUR);
            }            
        }
        counter = 0;
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
