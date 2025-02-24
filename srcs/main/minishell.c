#include "minishell.h"

char	*read_input(void)
{
	char *input;

	input = readline("minishell> "); // add input to history if not empty

	if (input && *input)
		add_history(input);
	return (input);
}

void    tokenize_and_split(t_minishell *minishell)
{
	t_list  *current;
	t_list  *split_tokens;
	t_list  *next;

	minishell->token = tokenize_input(minishell->input);
	if (!minishell->token)
		return ;
	current = minishell->token;
	while (current)
	{
		next = current->next;
		split_tokens = split_operators(current->content, 0, 0);
		if (!split_tokens)  // Handle this case
		{
			clear_token_list(minishell->token);
			minishell->token = NULL;
			return ;
		}
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
			ft_dprintf(STDERR_FILENO, "exit\n");
			break ;
		}
		tokenize_and_split(&minishell);
		//handle_expand_idk(&minishell); // -> working on it
		tmp_test = minishell.token;
		for (int i = 0; tmp_test != NULL; i++)
		{
			printf("Maillon ID: %d\nToken: [%s]\n", i, tmp_test->content);
			tmp_test = tmp_test->next;
		}
		create_ast(&minishell);
		// t_ast *test_tree = create_test_tree();
		// printf("\nArbre de syntaxe abstraite :\n");
		printf(BLUE"\nAST\n"RESET);
		print_ast(minishell.ast_node, 0);
		printf(PURPLE"\nEXEC"RESET);
		printf("\n");
		minishell.exit_status = exec_minishell(minishell.ast_node, &minishell);
		printf(YELLOW"\nEXIT STATUS\n"RESET);
		printf("exit status = %d\n", minishell.exit_status);
		// free_ast(test_tree);
		printf("--------------------\n");
		free(minishell.input);
		free_ast(minishell.ast_node);
	}
	rl_clear_history();
	free_env(&minishell);
	return (0);
}
