#include <stdbool.h>
#include <stdio.h>

#define MAX_LENGTH 1024

//''e''c'ho 'b''o"nj"o"'u'r" -> handle when quote take space too here ==> "echo "

void parse_input(const char *input)
{
	char	result[MAX_LENGTH];
	int		j = 0;
	int		i = 0;
	bool	inside_single_quote = false;
	bool	inside_double_quote = false;

	while (input[i])
	{
		if (input[i] == '\'' && !inside_double_quote)
		{
			if (inside_single_quote)
				inside_single_quote = false; // out of single quotes
			else
				inside_single_quote = true;  // enter single quotes
		}
		else if (input[i] == '\"' && !inside_single_quote)
		{
			if (inside_double_quote)
				inside_double_quote = false; // out of double quotes
			else
				inside_double_quote = true;  // enter doubel quotes
		}
		// if we are not in quotes, or in double quotes, or in single quotes
		else if ((inside_single_quote && !inside_double_quote) || (inside_double_quote && !inside_single_quote) || (!inside_single_quote && !inside_double_quote))
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	printf("Résultat parsé : '%s'\n", result);
}
