#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// cc minishell.c -o minishell -lreadline -lcurses

void parse_input(const char *input);

void print_history()
{
	HIST_ENTRY **history;
	int	i;

	history = history_list(); // not allowed
	i= 0;
	if (history)
	{
		while( history[i] != NULL)
		{
			printf("%d: %s\n", i + 1, history[i]->line);
			i++;
		}
	}
}

char* read_input(void)
{
	char *input;

	input = readline("minishell> ");
	// add input to history if not empty
	if (input && *input)
		add_history(input);
	return (input);
}

int	main(void)
{
	char	*input;
	while (1)
	{
		input = read_input();
		if (input == NULL) //ctrl d
		{
			printf("\nExiting minishell...\n");
			break;
		}
		printf("%s\n\n", input);
		parse_input(input);
		free(input);
	}
	printf("\n--- Historique des commandes ---\n");
	print_history();
	return (0);
}
