#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the RGB values of the pixel
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Calculate the average to get grayscale value
            int gray = round((red + green + blue) / 3.0);

            // Set all three components to the grayscale value
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get original RGB values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculate sepia values
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Cap the values at 255 if they exceed the max RGB value
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Swap pixels horizontally
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixel [i][j] with pixel [i][width - 1 - j]
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redTotal = 0, greenTotal = 0, blueTotal = 0;
            int count = 0;

            // Check the surrounding pixels within the 3x3 grid
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newRow = i + di;
                    int newCol = j + dj;

                    // Ensure the newRow and newCol are within the bounds of the image
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        redTotal += copy[newRow][newCol].rgbtRed;
                        greenTotal += copy[newRow][newCol].rgbtGreen;
                        blueTotal += copy[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            // Set the pixel's new values to the average of the surrounding pixels
            image[i][j].rgbtRed = round(redTotal / (float)count);
            image[i][j].rgbtGreen = round(greenTotal / (float)count);
            image[i][j].rgbtBlue = round(blueTotal / (float)count);
        }
    }
}
