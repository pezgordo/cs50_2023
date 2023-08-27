#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau(int letters, int words, int sentences);

int main(void)
{
    string complete_text = get_string("enter text: ");

    int letters = count_letters(complete_text);
    int words = count_words(complete_text);
    int sentences = count_sentences(complete_text);
    int grade = coleman_liau(letters, words, sentences);

    // printf("Text: %s\n", complete_text);
    // printf("%i letters\n", letters);
    // printf("%i words\n", words);
    // printf("%i sentences\n", sentences);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int char_count = 0;
    int string_length = strlen(text);

    for (int i = 0; i < string_length; i++)
    {
        if (isalnum(text[i]))
        {
            char_count += 1;
        }
    }
    return char_count;
}

int count_words(string text)
{
    int word_count = 1;
    int string_length = strlen(text);

    for (int i = 0; i < string_length; i++)
    {
        if (isspace(text[i]))
        {
            word_count += 1;
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    int sentence_count = 0;
    int string_length = strlen(text);

    for (int i = 0; i < string_length; i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentence_count += 1;
        }
    }
    return sentence_count;
}

int coleman_liau(int letters, int words, int sentences)
{
    float fletters = letters;
    float fwords = words;
    float fsentences = sentences;
    float index = (0.0588 * (fletters / fwords * 100) - 0.296 * (fsentences / fwords * 100) - 15.8);

    int round_index = round(index);

    return round_index;
}