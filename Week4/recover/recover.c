#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// bllock size: 512 byte
const int CHUNK = sizeof(uint8_t) * 512;

int main(int argc, char *argv[])
{
    // check for argument
    if (argc != 2)
    {
        printf("Usage: recover [file]\n");
        return 1;
    }

    // Open file
    char *file_path = argv[1];
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", file_path);
        return 1;
    }

    // number of files found
    int jpgs_found = 0;

    // creation of the buffer
    uint8_t *buffer = malloc(CHUNK);

    // creation of filename for output file
    char *file_name = malloc(sizeof(char) * 8);

    // creation of the output file
    FILE *output = NULL;

    // read input in 512 byte chunks
    while (fread(buffer, CHUNK, 1, file) != 0)
    {
        // found jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if there is an open file, close it
            if (output != NULL)
            {
                //printf("Closing file: %s\n", file_name);
                fclose(output);
            }

            // generate new file name
            sprintf(file_name, "%03i.jpg", jpgs_found);

            // open new file for writing
            output = fopen(file_name, "w");
            //printf("Opening file: %s\n", file_name);

            jpgs_found += 1;
        }

        // if open file, keep writing to it, else continue to next chunk
        if (output != NULL)
        {
            fwrite(buffer, CHUNK, 1, output);
            //printf("Writing to file: %s\n", file_name);
        }
    }

    fclose(output);
    fclose(file);
    free(buffer);
    free(file_name);

    return 0;
}