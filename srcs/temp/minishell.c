#include "minishell.h"

int	global_variable;

// void print_history()
// {
// 	HIST_ENTRY **history;
// 	int	i;

// 	history = history_list(); // not allowed
// 	i= 0;
// 	if (history)
// 	{
// 		while( history[i] != NULL)
// 		{
// 			printf("%d: %s\n", i + 1, history[i]->line);
// 			i++;
// 		}
// 	}
// }

// void	signal_handler(int signum) //ctrl c
// {
// 	if (signum == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// char* read_input(void)
// {
// 	char *input;

// 	input = readline("minishell> "); //221 leak
// 	// add input to history if not empty

// 	if (input && *input)
// 		add_history(input);
// 	return (input);
// }

// int	main(void)
// {
// 	char	*input;
// 	t_args	args;
// 	t_args	*temp_test;

// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, SIG_IGN);

// 	ft_memset(&args, 0, sizeof(t_args));
// 	// create_struct(&args);

// 	printf("args = %s, %d, %p\n\n", args.arg, args.token, args.next);

// 	while (1)
// 	{
// 		input = read_input();
// 		if (input == NULL) //ctrl d
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		practice(input, &args);
// 		temp_test = args.next;
// 		for (int i = 0; temp_test != NULL; i++)
// 		{
// 			printf("Maillon ID: %d\nToken value: %d\nArg value: %s\n", i, temp_test->token, temp_test->arg ? temp_test->arg : "(null)");
// 			temp_test = temp_test->next;
// 			printf("\n\n");
// 		}
// 		// temp_test = args.next;
// 		//parse_input(input, &args);
// 		free(input);
// 	}
// 	rl_clear_history();
// 	free_struct(&args);
// 	printf("-> end of main\n");
// 	return (0);
// }

void	create_struct(t_list *args)
{
	args->content = NULL;
	args->next = NULL;
}

void	add_node(t_list *args)
{
	t_list	*temp;
	t_list	*new_node;

	if (!args)
		return ;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	create_struct(new_node);
	if (!args->next)
	{
		args->next = new_node;
		return ;
	}
	temp = args->next;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	free_env(t_minishell *minishell)
{
	if (minishell->envp)
		free_list(minishell->envp);
	if (minishell->token)
		free_list(minishell->token);
}

void	signal_handler(int signum) //ctrl c
{
	if (signum == SIGINT)
	{
		global_variable = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		global_variable = SIGQUIT;
}

char* read_input(void)
{
	char *input;

	input = readline("minishell> "); // add input to history if not empty

	if (input && *input)
		add_history(input);
	return (input);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free(split);
		split = NULL;
	}
}

void	practice(t_minishell *minishell)
{
	t_list	*current;
	char	**split;
	size_t	i;

	if (!minishell || !minishell->token)
		return ;
	split = ft_split(minishell->input, ' ');
	if (!split)
		return ;
	current = minishell->token;
	while (current->next)
		current = current->next;
	i = 0;
	while (split[i])
	{
		add_node(current);
		current = current->next;
		if (current)
			current->content = ft_strdup(split[i]);
		i++;
	}
	free_split(split);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_list	*tmp_test;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))  // protection pour ./minishell | ./minishell par exemple
	{
		dprintf(STDERR_FILENO, "not a tty\n");
		return (1);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	//ft_memset(&minishell, 0, sizeof(t_minishell));
	minishell_init(&minishell, ac, av, envp);
	minishell.token = malloc(sizeof(t_list));
	if (!minishell.token)
		return (1);
	create_struct(minishell.token);
	while (1)
	{
		minishell.input = read_input();
		if (minishell.input == NULL) {// ctrl+d
			dprintf(STDERR_FILENO, "exit\n"); // changer pour notre propre printf sur sortie erreur
			break ;
		}
		practice(&minishell);
		tmp_test = minishell.token->next;
		for (int i = 0; tmp_test != NULL; i++)
		{
			printf("Maillon ID: %d\nArg value: %s\n", i, tmp_test->content ? (char *)tmp_test->content : "(null)");
			tmp_test = tmp_test->next;
			printf("\n");
		}
		printf("\n--------------------\n");
		free(minishell.input);
	}
	rl_clear_history();
	free_env(&minishell);
	return (0);
}
