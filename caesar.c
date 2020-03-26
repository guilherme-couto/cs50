#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool validkey (int size, string cmdline[]);

int main (int argc, string argv[])
{
    if (validkey (argc, argv) == false)
    {
        return 1;
    }

    int k = atoi(argv[1]);
    string pln = get_string("plaintext: ");


    for (int i = 0, m = strlen(pln); i < m; i ++)
    {
        //trocando minusculas
        if (pln[i] >= 'a' && pln[i] <= 'z')
        {
            if ((pln[i] + k) > 'z') //caso ultrapasse z
            {
                pln[i] = pln[i] + (k % 26);
            }
            else
            {
                pln[i] = pln[i] + k;
            }
        }

        //trocando maiusculas
        else if (pln[i] >= 'A' && pln[i] <= 'Z')
        {
            if ((pln[i] + k) > 'Z') //caso ultrapasse Z
            {
                pln[i] = pln[i] + + (k % 26);
            }
            else
            {
                pln[i] = pln[i] + k;
            }
        }

    }

    printf("ciphertext: %s\n", pln);

    return 0;

}


bool validkey (int size, string cmdline[]) //validar a chave
{
    if (size != 2) //just one key
    {
        printf("Usage: ./caesar key\n");
        return false;
    }
    else
    {
        for (int i = 0, n = strlen(cmdline[1]); i < n; i ++)
        {
            if (cmdline[1][i] < '0' || cmdline[1][i] > '9') //just numbers
            {
                printf("Usage: ./caesar key\n");
                return false;
            }
        }
        return true;
    }
}

