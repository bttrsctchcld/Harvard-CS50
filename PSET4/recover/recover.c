#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    FILE *file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Invalid submission.\n");
        return 1;
    }
    if (argc != 2)
    {
        printf("Please submit one (1) valid RAW file per command-line execution.\n");
        return 1;
    }
    FILE *img = NULL;
    int jpegcounter = 0;
    int isOpen = 0;
    unsigned char bytes[512];
    while (fread(bytes, 512, 1, file) == 1)
    {
        if (bytes [0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (isOpen == 1)
            {
                fclose(img);
            }
            else
            {
                isOpen = 1;
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", jpegcounter);
            img = fopen(filename, "w");
            jpegcounter++;
        }
        if (isOpen == 1)
        {
            fwrite(&bytes, 512, 1, img);
        }
    }
    fclose(file);
    fclose(img);
    return 0;
}