#include <cs50.h>
#include <ctype.h>
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
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    // Get the length of the word
    int word_length = strlen(word);

    // Convert all chars to lowercase
    for (int l = 0; l < word_length; l++)
    {
        word[l] = tolower(word[l]);
    }

    // create new array with the size of the alphabet
    char alpha[26];

    char c;
    int e;

    // Create a new array with index corresponding to letter of the alphabet
    for (c = 'a', e = 0; c <= 'z'; c++, e++)
    {
        alpha[e] = c;
    }

    // create an array the size of word
    int sum[word_length];

    // create an int that will store each value to be summed
    int total = 0;

    // loop through each char of word
    for (int d = 0; d < word_length; d++)
    {
        // assign target for each char in word
        char target = word[d];

        // check that the char is alphanumeric
        if (isalpha(target))
        {
            // loop through every letter on the alphabet in array alpha[]
            for (int t = 0; t <= 26; t++)
            {
                // if a letter is the same as target add the corresponding points to array sum[] which is the length of word
                if (alpha[t] == target)
                {
                    sum[d] = POINTS[t];
                }
            }
        }
        // if char in word is not alphanumric add 0 to array sum[]
        else
        {
            sum[d] = 0;
        }
    }

    // add all ints in array sum[]
    for (int s = 0; s < word_length; s++)
    {
        total += sum[s];
    }

    // return total
    return total;
}