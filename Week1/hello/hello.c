#include <stdio.h>
#include <cs50.h>


int main(void)
{
    // Ask user for their name and store it in variable name.
    string name = get_string("What is your name? ");

    // Interpolate the name to the greeting and print to the screen using printf.
    printf("Hello, %s!\n", name);
}