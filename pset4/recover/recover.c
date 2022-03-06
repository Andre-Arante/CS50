#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    // ''' make sure cmd arguemnt usage is correct '''
    if (argc != 2) {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    // ''' open memory card '''
    // open file in read mode using fopen
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File cannot be empty.");
        return 1;
    }

    // save space for an output file later on
    FILE *output = NULL;
    int image_counter = 0;
    int BLOCK_SIZE = 512;

    // save space for filename
    char *filename = malloc(sizeof(char) * 8);

    BYTE buffer[BLOCK_SIZE];

    // ''' Repeat until end of the card '''
    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE) {

        //check if new jpeg starts
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            // create a new file to write data to
            sprintf(filename, "%03i.jpg", image_counter);
            output = fopen(filename, "w");
            image_counter++;
        }

        // only write data if output is not null
        if(output != NULL) {
            fwrite(&buffer, sizeof(char), BLOCK_SIZE, output);
        }
    }

    // return memory once completed
    free(filename);
    fclose(file);
    fclose(output);

    return 0;
}