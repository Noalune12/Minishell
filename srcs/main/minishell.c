#include "minishell.h"
#include "heredoc.h"
#include "wildcard.h"

void	free_input_setup(char *tmp, char *exit_code, char *prompt)
{
	if (NULL != tmp)
		free(tmp);
	if (NULL != exit_code)
		free(exit_code);
	if (NULL != prompt)
		free(prompt);
}

char	*read_input(t_minishell *minishell)
{
	char	*input;
	char	*prompt;
	char	*tmp;
	char	*exit_code;
	int		code;

	code = minishell->exit_status;
	exit_code = ft_itoa(minishell->exit_status);
	tmp = ft_strjoin(RED"[", exit_code);
	if (tmp == NULL)
		return (NULL);
	free(exit_code);
	exit_code = ft_strjoin(tmp, RED"]> "RESET);
	if (exit_code == NULL)
	{
		free_input_setup(tmp, exit_code, NULL);
		return (NULL);
	}
	free(tmp);
	if (code == 0)
		prompt = ft_strjoin_free(GREEN_ARROW CYAN" minishell "RESET, exit_code);
	else
		prompt = ft_strjoin_free(RED_ARROW CYAN" minishell "RESET, exit_code);
	if (prompt == NULL)
	{
		free (exit_code);
		return (NULL);
	}
	input = readline(prompt);

	free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

void	close_free_and_reinit_fds(t_fd_info *fd)
{
	int	i;

	i = 0;
	while (i < fd->nb_elems)
	{
		close(fd->fds[i]);
		i++;
	}
	free(fd->fds);
	fd->fds = malloc(sizeof(int) * 10);
	fd->nb_elems = 0;
	fd->capacity = 10;
}

int event(void)
{
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	int			ret;
	// t_token		*tmp_test;

	minishell_init(&minishell, ac, av, envp);
	rl_event_hook = &event; // define callback function when rl_done is set at 1;
	while (1)
	{
		// printf("fd in capacity: %d\n", minishell.fds.fd_in.capacity);
		handle_signal_main(); // appel un peu tardif ?
		free_token_list(minishell.token);
		minishell.token = NULL;
		minishell.input = read_input(&minishell);
		if (g_signal_received != 0) // Check if Ctrl+C was pressed
		{
			minishell.exit_status = g_signal_received + 128;
			continue ;
		}
		if (minishell.input == NULL) // ctrl + d
		{
			ft_dprintf(STDERR_FILENO, "exit\n"); // TODO do not \n is in ./minishell
			break ;
		}
		init_global();
		minishell.token = tokenize_input(minishell.input, &minishell.exec_status);
		minishell.token = split_operators(minishell.token, &minishell.exec_status);
		minishell.token = expand_wildcards(minishell.token, &minishell.exec_status);
		check_heredoc(&minishell); //-> je parcours jusqu'a je tombe sur un "<< EOF "-> remplace par "< filename" dans token
		syntax_check(&minishell);
		minishell.ast_node = build_ast(&minishell.token, &minishell.exec_status);
		if (minishell.options->display_ast)
			print_ast(minishell.ast_node, 0, &minishell.exec_status);
		if (g_signal_received != 0) // Check if Ctrl+C was pressed
			minishell.exit_status = g_signal_received + 128;
		else if (minishell.ast_node)
		{
			minishell.exit_status = exec_minishell(minishell.ast_node, &minishell);
		}
		free(minishell.input);
		if (minishell.ast_node)
			free_ast(minishell.ast_node);
		if (minishell.fd_in)
			close(minishell.fd_in);
		if (minishell.fd_out)
			close(minishell.fd_out);
		close_free_and_reinit_fds(&minishell.fds.fd_in);
		close_free_and_reinit_fds(&minishell.fds.fd_out);
	}
	ret = minishell.exit_status;
	if (minishell.fd_in)
		close(minishell.fd_in);
	if (minishell.fd_out)
		close(minishell.fd_out);
	rl_clear_history();
	free_env(&minishell);
	return (ret);
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
// 	minishell_main_loop(&minishell);
// 	rl_clear_history();
// 	free_env(&minishell);
// 	return (EXIT_SUCCESS);
// }
