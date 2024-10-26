#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

// Function to check if a block is the start of a JPEG
int is_jpeg(uint8_t buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    FILE *output = NULL;
    int file_count = 0;
    char filename[8];

    while (fread(buffer, BLOCK_SIZE, 1, input) == 1)
    {
        if (is_jpeg(buffer))
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(filename, "%03i.jpg", file_count);
            file_count++;

            output = fopen(filename, "w");
            if (output == NULL)
            {
                fprintf(stderr, "Could not create file %s.\n", filename);
                return 1;
            }
        }

        if (output != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);

    return 0;
}
