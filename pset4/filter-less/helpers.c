#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {

            // find average RBG value
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            float avg = round((blue + green + red)/3);

            // set all values to avg
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i]  [j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int sepiaRed, sepiaGreen, sepiaBlue;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            // find values
            sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            // set values

            if(sepiaRed > 255) image[i][j].rgbtRed = 255;
            else image[i][j].rgbtRed = sepiaRed;

            if(sepiaGreen > 255) image[i][j].rgbtGreen = 255;
            else image[i][j].rgbtGreen = sepiaGreen;

            if(sepiaBlue > 255) image[i][j].rgbtBlue = 255;
            else image[i][j].rgbtBlue = sepiaBlue;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // i is the current row
    // j is the position in the row
    for(int i = 0; i < height; i++) {

        RGBTRIPLE new_row[width];
        int k = 0;

        // create copy of array
        for(int n = 0; n < width; n++) {
            new_row[n] = image[i][n];
        }

        // reverse row
        for(int j = width-1; j >= 0; j--) {
            image[i][j] = new_row[k];
            k++;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of image
    RGBTRIPLE cpy_img[height][width];

    float tred, tgreen, tblue, n;

    // blur temp image
    for(int i = 0; i < height; i++) {
        // for each pixel in image
        for(int j = 0; j < width; j++) {

            tred = tgreen = tblue = n = 0;

            // find all valid neighbors
            for(int x = -1; x < 2; x++) {
                for(int y = -1; y < 2; y++) {

                    int cx = x + i;
                    int cy = y + j;

                    // check for in bounds
                    if (cx < 0 || cx > (height - 1) || cy < 0 || cy > (width - 1))
                    {
                        // if out, move on
                        continue;
                    } else {
                        tred += image[cx][cy].rgbtRed;
                        tblue += image[cx][cy].rgbtBlue;
                        tgreen += image[cx][cy].rgbtGreen;

                        n++;
                    }
                }
            }

            // set that pixel to the avg
            cpy_img[i][j].rgbtRed = round(tred / n);
            cpy_img[i][j].rgbtGreen = round(tgreen / n);
            cpy_img[i][j].rgbtBlue = round(tblue / n);
        }
    }

    // copy temp to orginal
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j].rgbtRed = cpy_img[i][j].rgbtRed;
            image[i][j].rgbtGreen = cpy_img[i][j].rgbtGreen;
            image[i][j].rgbtBlue = cpy_img[i][j].rgbtBlue;
        }
    }

    return;
}
