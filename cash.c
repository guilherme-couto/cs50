#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;

    do
    {
       change = get_float("How much is owed? $");
    }
    while (change < 0.0); //only positive value

    int q = change / 0.25; //quarters
    int d = (change - (q * 0.25)) / 0.1; //dimes
    int n = (change - (q * 0.25) - (d * 0.1)) / 0.05;
    int p = (change - (q * 0.25) - (d * 0.1) - (n * 0.05)) / 0.01;
    
    printf("%d\n", q + d + n + p);

    
}
