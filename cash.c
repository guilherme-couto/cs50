#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;

    do
    {
        dollars = get_float("How much dollars is owed? $");
    }
    while (dollars < 0.0); //only positive value

    int change = round(dollars * 100);
    int q = 0, d = 0, n = 0, p = 0;

    while (change / 25 > 0) //quarters
    {
        q ++;
        change -= 25;
    }

    while (change / 10 > 0) //dimes
    {
        d ++;
        change -= 10;
    }

    while (change / 5 > 0) //nickels
    {
        n ++;
        change -= 5;
    }

    while (change / 1 > 0) //pennies
    {
        p ++;
        change -= 1;
    }

    printf("%d\n", q + d + n + p);
         
}
