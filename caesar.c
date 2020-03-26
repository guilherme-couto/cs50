#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool validkey (int size, string cmdline[]);
//char crypto (int k, string pln);

int main (int argc, string argv[])
{
    if (validkey (argc, argv) == false)
    {
        return 1;
    }

    int k = atoi(argv[1]);
    string pln = get_string("plaintext: ");
    string cph = {0};

    for (int i = 0, m = strlen(pln); i < m; i ++)
    {
        //trocando minusculas
        if ((char) pln[i] >= 'a' && (char) pln[i] <= 'z')
        {
            if (((char) (pln[i] + k)) > 'z')
            {
                cph[i] = pln[i] + k - 26 - (26 * (k / 26));
            }
            else
            {
                cph[i] = pln[i] + k;
            }
        }

        //trocando maiusculas
        else if ((char) pln[i] >= 'A' && (char) pln[i] <= 'Z')
        {
            if (((char) (pln[i] + k)) > 'Z')
            {
                cph[i] = pln[i] + k - 26 - (26 * (k / 26));
            }
            else
            {
                cph[i] = pln[i] + k;
            }
        }

        //mantendo demais caracteres
        else
        {
            cph[i] = pln[i];
        }
    }

    //crypto (key, plain);

    printf("ciphertext: %s\n", cph);

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

