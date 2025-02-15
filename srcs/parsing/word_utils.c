#include "minishell.h"

size_t get_word_length(char *input, size_t start)
{
    size_t i;
    char current_quote;

    i = 0;
    current_quote = 0;
    while (input[start + i] && input[start + i] != ' ' && input[start + i] != '\t')
    {
        if (is_quote(input[start + i]) && !current_quote)
            current_quote = input[start + i];
        else if (input[start + i] == current_quote)
            current_quote = 0;
        i++;
    }
    return (i);
}
