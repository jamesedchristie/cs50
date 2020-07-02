#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("Invalid file\n");
        return 2;
    }

    BYTE *buffer = malloc(513 * sizeof(BYTE));
    char *filename = malloc(8 * sizeof(char));
    FILE *img = NULL;
    int counter = 0;
    int read_no;

    while (fread(buffer, sizeof(BYTE), 512, f) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            counter++;
            if (counter == 1)
            {
                sprintf(filename, "%03i.jpg", counter - 1);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(f);
                    return 3;
                }
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            else
            {
                fclose(img);
                img = NULL;
                sprintf(filename, "%03i.jpg", counter - 1);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(f);
                    return 4;
                }
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
        else if (counter > 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    fclose(img);
    fclose(f);

    free(buffer);
    free(filename);
}
