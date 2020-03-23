#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How many bricks tall does the mario's pyramid will have?\n");
    int height = get_int("(insert a number between 1 and 8): ");
    
    if (height < 1 || height > 8)
    {
        do
        {
            height = get_int("(insert a number between 1 and 8): ");
        }
        while (height < 1 || height > 8);
    }

    for (int i = 1; i <= height; i++) //lines
    {
        //first pyramid
        for (int j = 1; j <= height; j++)
        {
            if (j + i > height) //condition to brick
            {
                printf("#"); //brick
            }
            else
            {
                printf(" "); //empty
            }
        }
        
        //gap
        printf("  ");

        //second pyramid
        for (int j = height + 3; j <= (2 * height) + 2; j++)
        {
            if (j <= (i + height + 2))
            {
                printf("#"); //brick
            }
            
        }
        printf("\n"); //new line
    }
}
