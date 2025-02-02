#include "minishell.h"


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

void	signal_handler(int signum) //ctrl c
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char* read_input(void)
{
	char *input;

	input = readline("minishell> "); //221 leak
	// add input to history if not empty

	if (input && *input)
		add_history(input);
	return (input);
}

int	main(void)
{
	char	*input;
	t_args	*args;
	t_args	*temp;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	args = NULL;
	args = create_struct(args);
	add_node(&args);
	temp = args->next;
	printf("args = %s, %d, %p\n\n", args->arg, args->token, args->next);
	printf("args = %s, %d, %p\n\n", temp->arg, temp->token, temp->next);

	while (1)
	{
		input = read_input();
		if (input == NULL) //ctrl d
		{
			printf("exit\n");
			break;
		}
		// printf("%s", input);
		parse_input(input, args);
		free(input);
	}
	rl_clear_history();
	free_struct(args);
	return (0);
}
