#include <cs50.h>
#include <stdio.h>



int main(void)
{
    int height;


    do
    {
        // Asking user for the height.
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); // Height lower than 1 and bigger than 8 is not permitted.


    int items = (height * 2) + 2;
    int gap = 2;
    int hashes;
    int spaces;


    for (int i = 0; i < height; i++)
    {
        // number of spaces per row.
        spaces = height - i - 1;

        // number of hashes per row.
        hashes = height - spaces;


        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }


        for (int j = 0; j < hashes; j++)
        {
            printf("#");
        }


        for (int j = 0; j < gap; j++)
        {
            printf(" ");
        }


        for (int j = 0; j < hashes; j++)
        {
            printf("#");
        }


        printf("\n");
    }
}