#include "types.h"
#include "ast.h"
#include "minishell.h"

static void	close_free_and_reinit_fds(t_fd_info *fd)
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

void	cleanup_loop(t_minishell *minishell)
{
	free(minishell->input);
	if (minishell->ast_node)
		free_ast_2(minishell);
	if (minishell->fd_in)
		close(minishell->fd_in);
	if (minishell->fd_out)
		close(minishell->fd_out);
	close_free_and_reinit_fds(&minishell->fds.fd_in);
	close_free_and_reinit_fds(&minishell->fds.fd_out);
}


void	cleanup_exit(t_minishell *minishell)
{
	if (minishell->fd_in)
		close(minishell->fd_in);
	if (minishell->fd_out)
		close(minishell->fd_out);
	rl_clear_history();
	cleanup_shell(minishell);
}
