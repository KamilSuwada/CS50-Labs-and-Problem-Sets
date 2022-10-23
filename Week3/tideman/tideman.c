#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_for_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Loop thrugh the candidates and check if their name matches the input:
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name of the candidate matches a candidate in the candidates array:
        if (strcmp(candidates[i], name) == 0)
        {
            // Locking the rank in.
            ranks[rank] = i;
            // Return true to indicate succesful ballot.
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop thrugh the candidates, except the last one:
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through candidates in the positions after current (j = i + 1) including the last one:
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Make a pair:
            if (preferences[i][j] > preferences[j][i]) // i wins over j
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //printf("winner: %s(%i votes)  loser: %s(%i votes)\n", candidates[i], preferences[i][j], candidates[j], preferences[j][i]);
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i]) // j wins over i
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                //printf("winner: %s(%i votes)  loser: %s(%i votes)\n", candidates[j], preferences[j][i], candidates[i], preferences[i][j]);
                pair_count += 1;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort the candidate pairs by their votes (number of candidate pairs will not be massive, so selection sort will be ok):
    // We need to iterate count - 1 times:
    for (int i = 0; i < pair_count - 1; i++)
    {
        int max = i; // index of the pair with the strongest victory.

        for (int j = i; j < pair_count; j++) // Looping through pairs leaving out the already sorted ones:
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) > (preferences[pairs[i].winner][pairs[i].loser]))
            {
                max = j;
            }
        }

        if (max != i) // If index of candidate pair is already at the desired position, continue to the next iteration, otheriwise:
        {
            pair temp_pair = pairs[i];
            pairs[i] = pairs[max];
            pairs[max] = temp_pair;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) // Loop through pairs.
    {
        if (check_for_cycle(pairs[i].winner, pairs[i].loser) == false) // check if there is cycle.
        {
            locked[pairs[i].winner][pairs[i].loser] = true; // lock the pair if no cycle is found.
        }
    }

    return;
}

// Function checks for cycles by following the arrow trail and comparing if the origin equals destination at any point.
bool check_for_cycle(int winner, int loser)
{
    if (winner == loser) // if last checked index ends up being the same as cycle start, then we have a cycle.
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++) // looping through candidates.
    {
        if (locked[loser][i] == true) // we found an arrow going from looser to i th candidate.
        {
            if (check_for_cycle(winner, i)) // if we follow that arrow further, recursievly, and find true, then we have a cycle.
            {
                return true;
            }
        }
    }

    return false; // no cycle was found.
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) // loop through candidates
    {
        int number_of_defeats = 0; // count of all defeats for a candidate.

        for (int j = 0; j < candidate_count; j++) // loop through all other candidates.
        {
            if (locked[j][i] == true) // if candidate j has won over candidate i: add one to defeats and break inner loop.
            {
                number_of_defeats += 1;
                break;
            }
        }

        if (number_of_defeats == 0) // if candidate has no defeats, they win!
        {
            printf("%s\n", candidates[i]);
            break; // we have a winner, no need to carry on the loop, so we break from it.
        }
    }

    return;
}