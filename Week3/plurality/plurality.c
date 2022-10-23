#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop thrugh the candidates and check if their name matches the input:
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name of the candidate matches a candidate in the candidates array:
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increment the votes by 1:
            candidates[i].votes += 1;
            // Return true to indicate succesful ballot.
            return true;
        }
    }
    // Input name was not matched!
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort the candidates by their votes (number of candidates will not be massive, so selection sort will be ok):
    // We need to iterate count - 1 times:
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int max = i; // index of the candidate with most votes in the iteration.

        for (int j = i; j < candidate_count; j++) // Looping through candidates leaving out the already sorted ones:
        {
            if (candidates[max].votes < candidates[j].votes) // Finding max number of votes candidate:
            {
                max = j;
            }
        }

        if (max != i) // If max number of votes candidate is already at the desired position, continue to the next iteration, otheriwise:
        {
            candidate temp_candidate = candidates[i];
            candidates[i] = candidates[max];
            candidates[max] = temp_candidate;
        }
    }

    int max_score = candidates[0].votes;

    for (int i = 0; i < candidate_count; i++) // Looping through candidates who have the same score, if not, loop breaks;
    {
        if (candidates[i].votes == max_score)
        {
            printf("%s\n", candidates[i].name);
        }
        else
        {
            break;
        }
    }

    return;
}