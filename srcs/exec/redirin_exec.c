#include "minishell.h"

// static void	open_dup_infile(t_ast *node, t_minishell *minishell)
// {
// 	minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY);
// 	if (minishell->fd_in == -1)
// 	{
// 		ft_dprintf(STDERR_FILENO, ERROR_INFILE, node->cmd->cmds[0]);
// 		error_handling_exec(minishell, NULL);
// 		exit (1);
// 	}
// 	if (dup2(minishell->fd_in, STDIN_FILENO) == -1)
// 	{
// 		close(minishell->fd_in); //TODO protect
// 		error_handling_exec(minishell, "dup2 failed");
// 		exit(1);
// 	}
// }

void add_fd(t_fd_info *fd, int fd_in)
{
	if (fd->nb_elems == fd->capacity)
	{
		fd->fds = realloc(fd->fds, sizeof(int) * fd->capacity + 10);;
		fd->capacity += 10;
	}
	fd->fds[fd->nb_elems] = fd_in;
	fd->nb_elems++;
}

void delete_fd(t_fd_info *fd, int nb_elem)
{
	int	i;

	i = nb_elem;
	while (i < fd->nb_elems - 1)
	{
		fd->fds[i] = fd->fds[i + 1];
		i++;
	}
	fd->nb_elems--;
}

int	handle_redirin(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	// if (minishell->fd_in)
	// 	close(minishell->fd_in);
	fd = open(node->cmd->cmds[0], O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	add_fd(&minishell->fds.fd_in, fd);
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_in, minishell->fds.fd_in.nb_elems - 1);
	close(fd);
	return (ret);
}
