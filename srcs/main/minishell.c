#include "minishell.h"

char	*read_input(void)
{
	char *input;

	input = readline("minishell> "); // add input to history if not empty

	if (input && *input)
		add_history(input);
	return (input);
}

void	tokenize_and_split(t_minishell *minishell)
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
		tokenize_and_split(&minishell);
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

// int	main(int ac, char **av, char **envp)
// {
// 	t_minishell	minishell;
// 	t_list		*tmp;

// 	tty_check();
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	minishell_init(&minishell, ac, av, envp);
// 	while (true)
// 	{
// 		clear_token_list(minishell.token);

// 	}
// }
