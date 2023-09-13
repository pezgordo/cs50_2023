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
    // TODO
    for (int i = 0; i < candidate_count; i++)

    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO


    int candidates_array[candidate_count];
    for (int c = 0; c < candidate_count; c++)
    {
        candidates_array[c] = c;
    }

    int preferences_recorded = 0;
    int comodin = -1;
    // For Each Rank the voter chose
    for (int r = 0; r < candidate_count; r++)
    {
            for (int i = 0; i < candidate_count; i++)
            {
                if (ranks[r] == candidates_array[i])
                {
                    for (int j = 0; j < candidate_count; j++)
                    {

                        if ((ranks[r] != candidates_array[j]) && (candidates_array[j] != comodin))
                        {
                                comodin = ranks[r];
                                preferences[ranks[r]][candidates_array[j]]++;
                                printf("i: %i j: %i\n", ranks[r], candidates_array[j]);

                                preferences_recorded++;

                                if (preferences_recorded >= candidate_count)
                                {
                                    return;
                                }
                        }
                    }
                }
            }
    }

    return;
    // DONE DONT TOUCH!!!
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    //DONE DONT TOUCH!!!
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {


            if (preferences[i][j] != preferences[j][i])
            {

                pair_count++;
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count - 1].winner = i;
                    pairs[pair_count -1].loser = j;
                }
                else
                {
                    pairs[pair_count - 1].winner = j;
                    pairs[pair_count -1].loser = i;
                }
            }
        }
    }

    return;
    // DONE DONT TOUCH!!!
}

// Sort pairs in decreasing orsder by strength of victory
void sort_pairs(void)
{
    // TODO

    int test = 0;
    int pair_strength[pair_count];


    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            if (preferences[i][j] != preferences[j][i])
            {
                test ++;

                if (preferences[i][j] > preferences[j][i])
                {
                    pair_strength[test -1] = preferences[i][j] - preferences[j][i];

                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pair_strength[test -1] = preferences[j][i] - preferences[i][j];

                }

            }
        }
    }

    int max = 0;

    for (int x = 0; x < pair_count; x++)
    {
        max = x;
        for (int y = x; y < pair_count; y++)
        {
            if(pair_strength[y] > pair_strength[max])
            {
                max = y;
            }
        }

        if (max != 0)
        {
            pair temp = pairs[x];

            pairs[x] = pairs[max];

            pairs[max] = temp;
        }

        //printf("pair_count: %i\n", pair_count);
        //printf("candidate_count: %i\n", candidate_count);
        printf("pairs[%i]: %i\n", x, pairs[x].winner);
        printf("pair_strength[%x]: %i\n", x,  pair_strength[x]);
        printf("test: %i\n", test);
    }



    return;

    //DONE DON'T TOUCH!!!!!
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ( i != j )
            {
                for (int x = 0; x < pair_count; x++)
                {
                    if ((pairs[x].winner == i) && (pairs[x].loser == j))
                    {
                        locked[i][j] = true;





                    }


                }


            }


        }

    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}