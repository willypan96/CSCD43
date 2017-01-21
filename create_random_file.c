#include "library.h"
#include <stdlib.h>
#include <stdio.h>

/* display usage */
int helper()
{
    printf("Usage: create_random_file <filename> <total bytes> <block size>\n");
    printf("<filename>: a filename (that does not exist) to be created in the current directory\n");
    printf("<total bytes>: (A number > 0) representing the number of bytes to be written to the file\n");
    printf("<block size>: (A number) representing the block size to emulate\n");
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        helper();
        return 1;
    }
    char *filename = argv[1];
    long numBytes = strtol(argv[2], NULL, 10);
    if (!numBytes)
    {
        // numbytes is 0 or NaN
        helper();
        return 1;
    }
    long blockSize = strtol(argv[3], NULL, 10);
    if (!blockSize)
    {
        //blockSize is 0 or NaN
        helper();
        return 1;
    }

    char *buffer;
    /* Initial memory allocation */
    buffer = (char *)malloc(blockSize);

    int index = 0;
    long cur_time = getMicrotime();
    FILE *fp = fopen(filename, "w");
    while (index < (numBytes / blockSize))
    {
        random_array(buffer, blockSize);
        fwrite(buffer, 1, blockSize, fp);
        fflush(fp);
        index++;
    }
    fclose(fp);
    long end_time = getMicrotime();
    printf("%ld", end_time - cur_time);
    return 0;
}