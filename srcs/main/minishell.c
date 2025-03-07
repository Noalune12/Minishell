#include "minishell.h"
#include "heredoc.h"

char	*read_input(t_minishell *minishell)
{
	char	*input;
	char	*prompt;
	char	*tmp;
	char	*exit_code;

	exit_code = ft_itoa(minishell->exit_status);
	tmp = ft_strjoin("[", exit_code);
	free(exit_code);
	exit_code = ft_strjoin(tmp, "]> ");
	free(tmp);
	prompt = ft_strjoin("minishell ", exit_code);
	free(exit_code);
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_token		*tmp_test;

	tty_check();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell_init(&minishell, ac, av, envp);
	printf("--------------------\n");
	while (1)
	{
		printf("signal = %d\n", return_global());
		printf("exit status = %d\n", minishell.exit_status);
		free_token_list(minishell.token);
		minishell.token = NULL;
		minishell.input = read_input(&minishell);
		if (minishell.input == NULL) // ctrl + d
		{
			ft_dprintf(STDERR_FILENO, "exit\n");
			break ;
		}
		if (return_global() == SIGINT) // Check if Ctrl+C was pressed
			minishell.exit_status = 130;
		init_global();
		minishell.token = tokenize_input(minishell.input);
		if (!minishell.token)
			continue ;
		minishell.token = split_operators(minishell.token);
		if (!minishell.token)
			continue ;
		check_heredoc(&minishell); //-> je parcours jusqu'a je tombe sur un "<< EOF "-> remplace par "< filename" dans token
		tmp_test = minishell.token;
		for (int i = 0; tmp_test != NULL; i++)
		{
			printf("%sMaillon ID: %d : Token: [%s], Type: %d%s\n",RED,
				   i, tmp_test->content, tmp_test->type, RESET);
			tmp_test = tmp_test->next;
		}
		minishell.ast_node = build_ast(&minishell.token);
		// t_ast *test_tree = create_test_tree();
		// printf("\nArbre de syntaxe abstraite :\n");
		printf(BLUE"\nAST\n"RESET);
		print_ast(minishell.ast_node, 0);
		if (return_global() == 2)
			minishell.exit_status = 130;
		else if (minishell.ast_node)
		{
			printf(PURPLE"\nEXEC"RESET);
			printf("\n");
			minishell.exit_status = exec_minishell(minishell.ast_node, &minishell);
		}
		if (return_global() == 2)
			minishell.exit_status = 130;
		printf(YELLOW"\nEXIT STATUS\n"RESET);
		printf("exit status = %d\n", minishell.exit_status);
		printf("--------------------\n");
		free(minishell.input);
		free_ast(minishell.ast_node);
	}
	rl_clear_history();
	free_env(&minishell);
	return (0);
}
