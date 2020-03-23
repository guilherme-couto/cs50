#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How many bricks tall does the mario's pyramid will have?\n");
    int height = get_int ("(insert a number between 1 and 8): ");
    
    if (height < 1 || height > 8)
    {
        do
        {
            height = get_int ("(insert a number between 1 and 8): ");
        }
        while (height < 1 || height > 8);
    }

    for (int i=1; i<=height; i++) //lines
    {
        for (int j=1; j<=height; j++) //columns
        {
            if (j+i > height) //condition to brick
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }

        }
        printf("\n"); //new line
    }

}
