#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    string text = get_string("Text: ");

    int number_of_letters = count_letters(text);
    int number_of_words = count_words(text);
    int number_of_sentences = count_sentences(text);

    //printf("letters: %i, words: %i, sentences: %i\n", number_of_letters, number_of_words, number_of_sentences);

    float L = (float)number_of_letters / (float)number_of_words * 100.0;
    float S = (float)number_of_sentences / (float)number_of_words * 100.0;

    //printf("L: %f, S: %f\n", L, S);

    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    //printf("index: %f\n", index);

    int i = round(index);

    //printf("i: %i\n", i);

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", i);
    }
}


int count_sentences(string text)
{
    int number_of_sentences = 0; // keeps track of the no. of sentences.

    for (int i = 0; i < strlen(text); i++) // looping through chars in text
    {
        char c = text[i];
        int j = (int)c;

        if (j == 33 || j == 46 || j == 63)
        {
            number_of_sentences += 1; // increment
        }
    }

    return number_of_sentences;
}


int count_words(string text)
{
    int number_of_words = 0; // keeps track of the no. of words.

    for (int i = 0; i < strlen(text); i++) // looping through chars in text
    {
        char c = text[i];
        int j = (int)c;

        if (j == 32)
        {
            number_of_words += 1; // increment
        }
    }

    return number_of_words + 1;
}


int count_letters(string text)
{
    int number_of_letters = 0; // keeps track of the number of letters.

    for (int i = 0; i < strlen(text); i++) // looping through chars in array
    {
        char c = (char)text[i]; // assignement of the char
        int index; // declaration of the index of the letter in ASCII.

        if (islower(c) > 0) // lowercase, index will be int in ASCII of the char - 97.
        {
            index = (int)c - 97;
        }
        else // uppercase, index will be int in ASCII of the char - 65.
        {
            index = (int)c - 65;
        }

        if (index >= 0 && index <= 26) // Only indexes between 0 and 26 inclusive are allowed to score.
        {
            number_of_letters += 1;
        }

    }

    return number_of_letters;
}