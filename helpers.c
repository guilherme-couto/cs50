#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //média das três cores
            int sum = image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen;

            //atualizando para a média
            image[i][j].rgbtBlue = round(sum / 3);
            image[i][j].rgbtRed = round(sum / 3);
            image[i][j].rgbtGreen = round(sum / 3);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //atualizando RED
            //caso seja maior que 255
            if (round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            }


            //atualizando GREEN
            //caso seja maior que 255
            if (round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            }

            //atualizando BLUE
            //caso seja maior que 255
            if (round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            }
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //estrutura auxiliar
        RGBTRIPLE aux;

        for (int min = 0, max = width - 1; min < max; min++, max--)
        {
            aux = image[i][max];
            image[i][max] = image[i][min];
            image[i][min] = aux;
        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE nova[height][width];

    //bytes do meio da imagem
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            //variáveis de soma por cor
            int sumR = 0, sumG = 0, sumB = 0;

            //sub matriz
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    sumR += image[i + a][j + b].rgbtRed;
                    sumG += image[i + a][j + b].rgbtGreen;
                    sumB += image[i + a][j + b].rgbtBlue;
                }
            }

            //atualização dos bytes para cópia blur
            nova[i][j].rgbtRed = round(sumR / 9);
            nova[i][j].rgbtGreen = round(sumG / 9);
            nova[i][j].rgbtBlue = round(sumB / 9);

        }
    }

    //bytes da linha superior e inferior
    for (int i = 0; i <= height - 1; i += height - 1)
    {
        for (int j = 1; j < width - 1; j++)
        {
            //variáveis de soma por cor
            int sumR = 0, sumG = 0, sumB = 0;

            if (i == 0)
            {
                //sub matriz
                for (int a = 0; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 6);
                nova[i][j].rgbtGreen = round(sumG / 6);
                nova[i][j].rgbtBlue = round(sumB / 6);
            }

            else
            {
                //sub matriz
                for (int a = -1; a < 1; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 6);
                nova[i][j].rgbtGreen = round(sumG / 6);
                nova[i][j].rgbtBlue = round(sumB / 6);
            }
        }
    }

    //bytes da coluna esquerda e direita
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j += width - 1)
        {
            //variáveis de soma por cor
            int sumR = 0, sumG = 0, sumB = 0;

            if (j == 0)
            {
                //sub matriz
                for (int a = -1; a < 2; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 6);
                nova[i][j].rgbtGreen = round(sumG / 6);
                nova[i][j].rgbtBlue = round(sumB / 6);
            }

            else
            {
                //sub matriz
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 6);
                nova[i][j].rgbtGreen = round(sumG / 6);
                nova[i][j].rgbtBlue = round(sumB / 6);
            }
        }
    }

    //bytes dos cantos
    for (int i = 0; i <= height - 1; i += height - 1)
    {
        for (int j = 0; j <= width - 1; j += width - 1)
        {
            //variáveis de soma por cor
            int sumR = 0, sumG = 0, sumB = 0;

            if ((i + j) == 0)
            {
                //sub matriz
                for (int a = 0; a < 2; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 4);
                nova[i][j].rgbtGreen = round(sumG / 4);
                nova[i][j].rgbtBlue = round(sumB / 4);
            }

            else if (i == 0 && j == width - 1)
            {
                //sub matriz
                for (int a = 0; a < 2; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 4);
                nova[i][j].rgbtGreen = round(sumG / 4);
                nova[i][j].rgbtBlue = round(sumB / 4);
            }

            else if (i == height - 1 && j == 0)
            {
                //sub matriz
                for (int a = -1; a < 1; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 4);
                nova[i][j].rgbtGreen = round(sumG / 4);
                nova[i][j].rgbtBlue = round(sumB / 4);
            }

            else if (i == height - 1 && j == width - 1)
            {
                //sub matriz
                for (int a = -1; a < 1; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        sumR += image[i + a][j + b].rgbtRed;
                        sumG += image[i + a][j + b].rgbtGreen;
                        sumB += image[i + a][j + b].rgbtBlue;
                    }
                }

                //atualização dos bytes para cópia blur
                nova[i][j].rgbtRed = round(sumR / 4);
                nova[i][j].rgbtGreen = round(sumG / 4);
                nova[i][j].rgbtBlue = round(sumB / 4);
            }
        }
    }

    //atualizar imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = nova[i][j].rgbtRed;
            image[i][j].rgbtGreen = nova[i][j].rgbtGreen;
            image[i][j].rgbtBlue = nova[i][j].rgbtBlue;
        }
    }


    return;
}
