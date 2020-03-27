#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string txt, int n);
int count_words(string txt, int n);
int count_sentences(string txt, int n);

int main(void)
{
    string text = get_string("Text: ");

    int lenght = strlen(text);

    int letters = count_letters(text, lenght);
    int words = count_words(text, lenght);
    int sentences = count_sentences(text, lenght);

    float L = letters * (100.0 / words); //.0 por ser float
    float S = sentences * (100.0 / words); //.0 por ser float

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index >= 16.0) //em casos >= 16
    {
        printf("Grade 16+\n");
        return 0;
    }

    if (index < 1.0) //em casos < 1
    {
        printf("Before Grade 1\n");
        return 0;
    }

    printf("Grade: %.0f\n", round(index)); //demais casos


}


int count_letters(string txt, int n) //number of letters
{
    int numl = 0;

    for (int i = 0; i < n; i ++)
    {
        if (txt[i] >= 'A' && txt[i] <= 'z') //primeiro conjunto
        {
            if (txt[i] <= 'Z' || txt[i] >= 'a') //segundo conjunto
            {
                numl ++;
            }
        }
    }

    return numl;
}


int count_words(string txt, int n) //number of words
{
    int numw = 0;

    for (int j = 0; j < n; j ++)
    {
        if (txt[j] == ' ') //number of spaces = number of words - 1
        {
            numw ++;
        }
    }

    return numw + 1; //+1 pra corrigir a primeira palavra
}


int count_sentences(string txt, int n) //number of sentences
{
    int nums = 0;

    for (int k = 0; k < n; k ++)
    {
        if (txt[k] == '.' || txt[k] == '!' || txt[k] == '?') //possíveis fins de frases
        {
            nums ++;
        }
    }

    return nums;
}