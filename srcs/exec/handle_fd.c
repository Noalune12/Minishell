#include "minishell.h"

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

void dup_fd(t_fd_info *fd, int fd_redirect)
{
	if (fd->nb_elems > 0)
		dup2(fd->fds[fd->nb_elems - 1], fd_redirect); // TODO protect
}

void	close_fd(t_fd_info *fd)
{
	int	i;

	i = 0;
	while (i < fd->nb_elems)
	{
		close(fd->fds[i]); //TODO protect
		i++;
	}
}
