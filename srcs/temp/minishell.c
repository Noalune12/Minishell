#include "minishell.h"

int	g_global_variable;

void	create_struct(t_list *args)
{
	args->content = NULL;
	args->next = NULL;
}

void	add_node_test(t_list *args)
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
		g_global_variable = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		g_global_variable = SIGQUIT;
}

char	*read_input(void)
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

bool	replace_token(t_list *current, t_list *new_tokens)
{
	t_list	*next;
	t_list	*new_next;

	if (!new_tokens)
		return (true);
	next = current->next;
	free(current->content);
	current->content = ft_strdup(new_tokens->content);
	if (!current->content)
		return (false);
	current->next = new_tokens->next;
	free(new_tokens);
	if (!current->next)
	{
		current->next = next;
		return (true);
	}
	new_next = ft_lstlast(current->next);
	new_next->next = next;
	return (true);
}

void	practice(t_minishell *minishell)
{
	t_list	*current;
	t_list	*split_tokens;
	t_list	*next;

	minishell->token = tokenize_input(minishell->input);
	if (!minishell->token)
		return ;
	current = minishell->token;
	while (current)
	{
		next = current->next;
		split_tokens = split_operators(current->content);
		if (!replace_token(current, split_tokens))
		{
			clear_token_list(minishell->token);
			minishell->token = NULL;
			return ;
		}
		current = next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_list	*tmp_test;

	tty_check();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell_init(&minishell, ac, av, envp);
	printf("--------------------\n");
	while (1)
	{
		clear_token_list(minishell.token);
		minishell.input = read_input();
		if (minishell.input == NULL) // ctrl + d
		{
			dprintf(STDERR_FILENO, "exit\n"); // changer pour notre propre printf sur sortie erreur
			break ;
		}
		practice(&minishell);
		tmp_test = minishell.token;
		for (int i = 0; tmp_test != NULL; i++)
		{
			printf("Maillon ID: %d\nToken: '%s'\n", i, tmp_test->content);
			tmp_test = tmp_test->next;
		}
		// t_ast *test_tree = create_test_tree();
		// printf("\nArbre de syntaxe abstraite :\n");
		// print_ast(test_tree, 0);
		// free_ast(test_tree);
		printf("--------------------\n");
		free(minishell.input);
	}
	rl_clear_history();
	free_env(&minishell);
	return (0);
}
