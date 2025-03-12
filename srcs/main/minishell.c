#include "minishell.h"
#include "heredoc.h"
#include "wildcard.h"

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
	// (void)minishell;
	// input = readline("minishell$>");
	if (input && *input)
		add_history(input);
	return (input);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_token		*tmp_test;

	tty_check();
	minishell_init(&minishell, ac, av, envp);
	// printf("%s%s%s\n", BLUE, minishell.options.display_ast ? "true" : "false", RESET);
	// printf("%s%s%s\n", RED, minishell.exec_status ? "true" : "starting", RESET);
	while (1)
	{
		handle_signal_main(); // appel un peu tardif ?
		free_token_list(minishell.token);
		minishell.token = NULL;
		minishell.input = read_input(&minishell);
		if (minishell.input == NULL) // ctrl + d
		{
			ft_dprintf(STDERR_FILENO, "exit\n");
			break ;
		}
		if (g_signal_received != 0) // Check if Ctrl+C was pressed
			minishell.exit_status = g_signal_received + 128;
		init_global();
		check_entry(&minishell);
		// check_options_entry(&minishell); // A CONTINUER
		minishell.token = tokenize_input(minishell.input, &minishell.exec_status);
		// printf("%stokenize_input%s\n", minishell.exec_status ? GREEN : RED, RESET);
		minishell.token = split_operators(minishell.token, &minishell.exec_status);
		// printf("%ssplit_operators%s\n", minishell.exec_status ? GREEN : RED, RESET);
		tmp_test = minishell.token;

		minishell.token = expand_wildcards(minishell.token, &minishell.exec_status);
		//printf("%sexpand_wildcards%s\n", minishell.exec_status ? GREEN : RED, RESET);
		tmp_test = minishell.token;
		syntax_check(&minishell);
		check_heredoc(&minishell); //-> je parcours jusqu'a je tombe sur un "<< EOF "-> remplace par "< filename" dans token
		// printf("%ssyntax_check%s\n", minishell.exec_status ? GREEN : RED, RESET);
		minishell.ast_node = build_ast(&minishell.token, &minishell.exec_status);
		//printf("%sbuild_ast%s\n", minishell.exec_status ? GREEN : RED, RESET);
		//printf(BLUE"\nAST\n"RESET);

		//print_ast(minishell.ast_node, 0, &minishell.exec_status);
		// for (int i = 0; tmp_test != NULL; i++)
		// {
		// 	printf("%sMaillon ID: %d : Token: [%s], Type: %d%s\n",RED,
		// 		   i, tmp_test->content, tmp_test->type, RESET);
		// 	tmp_test = tmp_test->next;
		// }
		minishell.token = expand_wildcards(minishell.token, &minishell.exec_status);
		// printf("%sexpand_wildcards%s\n", minishell.exec_status ? GREEN : RED, RESET);
		tmp_test = minishell.token;
		syntax_check(&minishell);
		check_heredoc(&minishell); //-> je parcours jusqu'a je tombe sur un "<< EOF "-> remplace par "< filename" dans token
		// printf("%ssyntax_check%s\n", minishell.exec_status ? GREEN : RED, RESET);
		minishell.ast_node = build_ast(&minishell.token, &minishell.exec_status);
		// printf("%sbuild_ast%s\n", minishell.exec_status ? GREEN : RED, RESET);
		// printf(BLUE"\nAST\n"RESET);
		// print_ast(minishell.ast_node, 0, &minishell.exec_status);
		if (g_signal_received != 0) // Check if Ctrl+C was pressed
			minishell.exit_status = g_signal_received + 128;

		else if (minishell.ast_node)
		{
			// printf(PURPLE"\nEXEC"RESET);
			// printf("\n");
			minishell.exit_status = exec_minishell(minishell.ast_node, &minishell);
			// printf("%sexec_minishell%s\n", minishell.exec_status ? GREEN : RED, RESET);
		}
		// if (g_signal_received != 0) // Check if Ctrl+C was pressed
		// 	minishell.exit_status = g_signal_received + 128;
		// printf(YELLOW"\nEXIT STATUS\n"RESET);
		// printf("exit status = %d\n", minishell.exit_status);
		// printf("--------------------\n");
		free(minishell.input);
		if (minishell.ast_node)
			free_ast(minishell.ast_node);
		if (minishell.fd_in)
			close(minishell.fd_in);
		if (minishell.fd_out)
			close(minishell.fd_out);
	}
	if (minishell.fd_in)
		close(minishell.fd_in);
	if (minishell.fd_out)
		close(minishell.fd_out);
	rl_clear_history();
	free_env(&minishell);
	return (0);
}

/**
 * delete t_token *tmp_test
 *
 */
// void	minishell_main_loop(t_minishell *minishell)
// {
// 	t_token	*tmp;

// 	while (1)
// 	{
// 		free_token_list(minishell->token);
// 		minishell->token = NULL;
// 		minishell->input = read_input(minishell);
// 		if (minishell->input == NULL)
// 		{
// 			ft_dprintf(STDERR_FILENO, "exit\n");
// 			break ;
// 		}
// 		if (return_global == SIGINT)
// 			minishell->exit_status = 130;
// 		init_global();
// 		minishell->token = tokenize_input(minishell->input, &minishell->exec_status);
// 		printf("%sshould we continue execution: %s%s\n", GREEN, minishell->exec_status ? "true" : "false", RESET);
// 		minishell->token = split_operators(minishell->token, &minishell->exec_status);
// 		printf("%s%s%s\n", RED, minishell->exec_status ? "true" : "false", RESET);
// 		check_heredoc(minishell);
// 	}
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_minishell	minishell;

// 	minishell_init(&minishell, ac, av, envp);

// 	/* debug */
// 	printf("%sexec_status: %s%s\n", RED, minishell.exec_status ? "true" : "false", RESET);

// 	minishell_main_loop(&minishell);
// 	rl_clear_history();
// 	free_env(&minishell);
// 	return (EXIT_SUCCESS);
// }
