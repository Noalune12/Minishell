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

void	initialize_args(t_args *args)
{
	args->arg = NULL;
	args->token = 0;
	args->next = NULL;
}

int	main(void)
{
	char	*input;
	t_args	args;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

	create_struct(&args);
	add_node(&args);

	printf("args = %s, %d, %p\n\n", args.arg, args.token, args.next);

	while (1)
	{
		input = read_input();
		if (input == NULL) //ctrl d
		{
			printf("exit\n");
			break;
		}
		// printf("%s", input);
		parse_input(input, &args);
		free(input);
	}
	rl_clear_history();
	free_struct(&args);
	printf("done");
	return (0);
}
