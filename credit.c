#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long card = get_long("Card number: ");
   
    if ((card / (pow(10, 12))) == 0) //only card numbers
    {
        printf("INVALID\n");
    }

    else
    {

        int fsum = 0;
        long aux = 0;
    
        for (int i = 1; i < 16; i += 2)
        {
            aux = (card / pow(10, (i)));

            if ((((aux % 10) * 2) / 10) == 0)
            {
                fsum = fsum + ((aux % 10) * 2); //sum with one digit
            }
            else
            {
                //separete sum for 2 digits
                fsum = fsum + (((aux % 10) * 2) / 10);
                fsum = fsum + (((aux % 10) * 2) % 10);
            }
        }
    
        for (int j = 0; j < 16; j += 2)
        {
            aux = (card / pow(10, (j)));
            fsum = fsum + (aux % 10); //sum the remaining digits
        }

        int amex, visa13, visa16, master; //auxs to make comparation easier

        amex = (card / (pow(10, 13)));
        visa13 = (card / (pow(10, 12)));
        visa16 = (card / (pow(10, 15)));
        master = (card / (pow(10, 14)));

        if ((fsum % 10) != 0)
        {
            printf("INVALID\n");
        }

        else if (amex == 34 || amex == 37) //if amex
        {
            printf("AMEX\n");
        }

        else if (visa13 == 4 || visa16 == 4) //if visa
        {
            printf("VISA\n");
        }

        else if (master >= 51 && master <= 55) //if mastercard
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }

    } 
}
