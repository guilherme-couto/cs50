#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //prompt two words
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open file
    FILE *file = fopen(argv[1], "r");


    //check if file exists
    if (file == NULL)
    {
        return 1;
    }


    //read file
    BYTE arr[512];


    //encontrar o primeiro jpeg
    do
    {
        fread(arr, sizeof(BYTE), 512, file);
    }
    while (arr[0] != 0xff && arr[1] != 0xd8 && arr[2] != 0xff && (arr[3] & 0xf0) != 0xe0);

    //inicializações
    int i = 0;
    sprintf(argv[1], "%03i.jpg", i);
    FILE *img = fopen(argv[1], "w");

    //continunar busca
    while ('TRUE')
    {

        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] & 0xf0) == 0xe0)
        {


            fwrite(arr, sizeof(BYTE), 512, img);
            fread(arr, sizeof(BYTE), 512, file);


            while (arr[0] != 0xff || arr[1] != 0xd8 || arr[2] != 0xff || (arr[3] & 0xf0) != 0xe0)
            {
                fwrite(arr, sizeof(BYTE), 512, img);
                fread(arr, sizeof(BYTE), 512, file);
                //printf("2- %i %i %i %i\n", arr[0], arr[1], arr[2], arr[3]);
            }

            //printf("Alou\n");
            fclose(img);
            i ++;

            if (i == 49)
            {
                fclose(file);
                return 0;
            }

            sprintf(argv[1], "%03i.jpg", i);
            img = fopen(argv[1], "w");

        }

    }
    //free(arr);
    fclose(file);
    return 0;

}
