#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool validkey(int size, string cmdline[]);


int main(int argc, string argv[])
{
    if (validkey(argc, argv) == false)  //validar chave
    {
        return 1;
    }

    string pln = get_string("plaintext: ");

    for (int i = 0, n = strlen(pln); i < n; i ++)
    {
        int aux = 0;

        if (pln[i] >= 'A' && pln[i] <= 'Z') //avaliar maiusculas
        {
            aux = pln[i] - 65;

            if (islower(argv[1][aux]) != 0) //converter maiuscula em minuscula
            {
                pln[i] = argv[1][aux] - 32;
            }
            else //manter maiuscula
            {
                pln[i] = argv[1][aux];
            }
        }

        else if (pln[i] >= 'a' && pln[i] <= 'z') //avaliar minuscula
        {
            aux = pln[i] - 97;

            if (islower(argv[1][aux]) != 0) //manter minusculas
            {
                pln[i] = argv[1][aux];
            }
            else //converter minuscula em maiuscula
            {
                pln[i] = argv[1][aux] + 32;
            }
        }

    }

    printf("ciphertext: %s\n", pln); //imprimir

    return 0;
}


bool validkey(int size, string cmdline[])  //validar a chave
{
    if (size != 2) //just one key
    {
        printf("Usage: ./caesar key\n");
        return false;
    }

    int n = strlen(cmdline[1]);

    if (n != 26) //26 letras
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }



    for (int i = 0; i < n; i ++)
    {

        if (cmdline[1][i] < 'A' || cmdline[1][i] > 'Z') //serem só letras
        {
            if (cmdline[1][i] < 'a' || cmdline[1][i] > 'z')
            {
                printf("Key must only contain alphabetic characters.\n");
                return false;
            }
        }
        else
        {
            for (int a = 0; cmdline[1][a] != '\0'; a ++) //não ter letras repetidas
            {
                for (int b = 1; cmdline[1][b] != '\0'; b++)
                {
                    if (cmdline[1][a] == cmdline[1][b] || cmdline[1][a] == (cmdline[1][b] + 32) || cmdline[1][a] == (cmdline[1][b] - 32))
                    {
                        printf("Key must not contain repeated characters.\n");
                        return false;
                    }

                }
            }
        }

    }

    return true;
}