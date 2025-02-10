#include "../../incs/minishell.h"

/*
COLOR CODE :
- YELLOW = debug message
- PURPLE = print terminal
- RED = error
*/

void	get_echo_info(char *input, int *i, int *no_nl)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	if (!input[*i])
		printf(YELLOW"echo has no agument\n"RESET);
	if (input[*i] && input[*i + 1] && strncmp(input + *i, "-n", 2) == 0) // check if flag -n
	{
		if (!input[*i + 2] || (input[*i + 2] && input[*i + 2] == ' '))
		{
			*no_nl = 1;
			printf(YELLOW"no nl\n"RESET);
			*i += 2;
		}
	}
	while (input[*i]) // /!\ only -n no print
	{
		if (input[*i] == ' '
			&& (input[*i + 1] && input[*i + 2] && strncmp(input + *i + 1, "-n", 2) == 0)
			&& (!input[*i + 3] || (input[*i + 3] && input[*i + 3] == ' ')))
			*i += 3;
		else
			break ;
	}
}

void	ft_print_echo(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			while (input[i + 1] && input[i + 1] == ' ') // handle in parsing rm extra space
			i++;
		}
		printf(PURPLE"%c"RESET, input[i]);
		i++;
	}
}

void	ft_echo(char *input) // if pipe after write in pipe + adapt with struct
{
	int no_nl = 0;
	int i = 4;

	if (input[i] && input[i] != ' ')
	{
		printf(RED"bash: %s: command not found\n"RESET, input);
		return ;
	}
	get_echo_info(input, &i, &no_nl);
	if (no_nl && !input[i])
		printf(YELLOW"echo -n has no agument\n"RESET);
	while (input[i] && input[i] == ' ')
		i++;
	ft_print_echo(input + i);
	if (!no_nl)
		printf("\n");
}
