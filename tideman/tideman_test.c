#include <cs50.h>
#include <stdio.h>
#define MAX 9


int main(void)
{   int cand = 3;
    int candidate_count[3] = {0, 1, 2};

    // Max number of candidates


// preferences[i][j] is number of voters who prefer i over j
   // int preferences[MAX][MAX];

    int pair_count = 0;
   for (int i = 0; i < cand; i++)
    {
        for (int j = i + i; j < cand; j ++)
        {

            if (i != j)
            {
                pair_count++;
                printf("paid: (%i, %i)\n", candidate_count[i], candidate_count[j]);
                printf("pair count: %i\n", pair_count);
            }
        }
    }

}