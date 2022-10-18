#include <cs50.h>
#include <stdio.h>


// getting a digit from a number at index (counting from right)
int get_digit_at(long card, int index)
{
    long divider = 1;
    int i;

    for (i = index; i > 0; i--)
    {
        divider = divider * 10;
    }

    long digit = card % divider;
    divider = divider / 10;
    long remainder = card % divider;
    digit = digit - remainder;
    digit = digit / divider;

    return digit;
}


// checks if the index is of the last digit, => getting length.
bool is_index_last(long card, int index)
{
    long divider = 1;
    int i;

    for (i = index; i > 0; i--)
    {
        divider = divider * 10;
    }

    long digit = card % divider;


    // if the card number is equal to remainder, this means that this is the last digit.
    if (digit == card)
    {
        return true;
    }
    else // Not a last digit.
    {
        return false;
    }
}



int main(void)
{
    long card_number;


    card_number = get_long("Number: ");


    int length = 1;
    int sum = 0;


    while (true)
    {
        int digit = get_digit_at(card_number, length);
        bool is_last = is_index_last(card_number, length);
        int num;


        if (length % 2 == 0) // if length % 2 is 0 => every other file from the second last.
        {
            num = digit * 2;

            if (num < 10) // if number is less than 10, the sum of the digits = number.
            {
                sum = sum + num;
            }
            else // if not, sum of the digit is equal first (2) and second (1) digit.
            {
                int units = get_digit_at(num, 1);
                int tens = get_digit_at(num, 2);
                sum = sum + units + tens;
            }
        }
        else // if not every other, no need to multiply x 2, just add to sum.
        {
            sum = sum + digit;
        }


        length++;


        if (is_last == true) // if last one, breaking from the while loop.
        {
            length--; // we started from 1, so assumed there will be one digit extra, hence -1 here.
            break;
        }
    }

    int last_digit_of_sum = get_digit_at(sum, 1); // getting the last digit of the sum.


    if (last_digit_of_sum == 0)
    {
        if (length == 13) // length 13
        {
            if (get_digit_at(card_number, 13) == 4) // starts with 4.
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 15) // length 15
        {
            int first_two_digits = get_digit_at(card_number, 14) + get_digit_at(card_number, 15) * 10; // getting the first two numbers as int.

            if (first_two_digits == 34 || first_two_digits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 16)
        {
            int first_two_digits = get_digit_at(card_number, 15) + get_digit_at(card_number, 16) * 10;

            if (get_digit_at(card_number, 16) == 4)
            {
                printf("VISA\n");
            }
            else if (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53)
            {
                printf("MASTERCARD\n");
            }
            else if (first_two_digits == 54 || first_two_digits == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }



    //printf("\n\nLength: %i  sum: %i last_digit: %i\n", length, sum, last_digit_of_sum);
}