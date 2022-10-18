#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};


int compute_score(string word);


int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner


    if (score1 > score2) // Player 1 wins
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2) // Player 2 wins
    {
        printf("Player 2 wins!\n");
    }
    else // Tie
    {
        printf("Tie!\n");
    }
}



int compute_score(string word)
{
    // TODO: Compute and return score for string

    int score = 0; // keeps track of the score.

    for (int i = 0; i < strlen(word); i++) // looping through chars in array
    {
        char c = (char)word[i]; // assignement of the char
        int index; // declaration of the index

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
            score += POINTS[index];
        }

    }

    return score; // returns score.
}
