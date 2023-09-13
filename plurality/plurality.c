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
} candidate;

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int winner_votes = candidates[0].votes;
    string winner_name = candidates[0].name;

    int tie_votes = 0;
    string tie_name = "tie";

    int all_tied = 1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winner_votes)
        {
            winner_votes = candidates[i].votes;
            winner_name = candidates[i].name;
        }
    }

    for (int c = 0; c < candidate_count; c++)
    {
        if ((candidates[c].votes == winner_votes) && (candidates[c].name != winner_name))
        {
            tie_votes = candidates[c].votes;
            tie_name = candidates[c].name;
        }
    }

    for (int s = 0; s < candidate_count; s++)
    {
        if (candidates[s].votes != candidates[0].votes)
        {
            all_tied = 0;
            break;
        }
    }

    if (all_tied == 1)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    else if (strcmp(tie_name, "tie") == 0)
    {
        printf("%s\n", winner_name);
    }
    else
    {
        printf("%s\n%s\n", winner_name, tie_name);
    }
    return;
}