#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg, final, sum = 0;
            sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            avg = sum / 3;
            final = round(avg);
            image[i][j].rgbtRed = final;
            image[i][j].rgbtGreen = final;
            image[i][j].rgbtBlue = final;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp;
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    float sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
    int resRed, resBlue, resGreen;
    
    for (int i = 0; i < height; i++)
    {
       for (int j = 0; j < width; j++)
       {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && j + l >= 0 && i + k < height && j + l < width)
                    {
                        sumRed += image[i + k][j + l].rgbtRed;
                        sumGreen += image[i + k][j + l].rgbtGreen;
                        sumBlue += image[i + k][j + l].rgbtBlue;
                        count++;
                    }
                }
            }
            
            resRed = round(sumRed / count);
            resBlue = round(sumBlue / count);
            resGreen = round(sumGreen / count);
            
            sumRed = 0, sumBlue = 0, sumGreen = 0, count = 0;
            
            copy[i][j].rgbtRed = resRed;
            copy[i][j].rgbtBlue = resBlue;
            copy[i][j].rgbtGreen = resGreen;
       }
       
    }
    
    for (int i = 0; i < height; i++)
    {
       for (int j = 0; j < width; j++)
       {
           image[i][j] = copy[i][j];
       }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    float redGx = 0, blueGx = 0, greenGx = 0;
    float redGy = 0, blueGy = 0, greenGy = 0;
    int resRed, resBlue, resGreen;
    int Gx[3][3];
    int Gy[3][3];
    
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[1][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;
    
    Gy[0][0] = -1;
    Gy[0][1] = -2;
    Gy[0][2] = -1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[1][2] = 0;
    Gy[2][0] = 1;
    Gy[2][1] = 2;
    Gy[2][2] = 1;
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && j + l >= 0 && i + k < height && j + l < width)
                    {
                        redGx += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        greenGx += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        blueGx += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    
                        redGy += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                        greenGy += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                        blueGy += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            
            resRed = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));
            resBlue = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));
            resGreen = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));
            
            redGx = 0, blueGx = 0, greenGx = 0;
            redGy = 0, blueGy = 0, greenGy = 0;
            
            if (resRed > 255)
            {
                resRed = 255;
            }
            
            if (resBlue > 255)
            {
                resBlue = 255;
            }
            
            if (resGreen > 255)
            {
                resGreen = 255;
            }
            
            copy[i][j].rgbtRed = resRed;
            copy[i][j].rgbtBlue = resBlue;
            copy[i][j].rgbtGreen = resGreen;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}
