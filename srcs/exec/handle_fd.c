/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:46 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:30:51 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "fd.h"

static int	*ft_realloc(int *tab, int len, int nb_elem)
{
	int	*ret;
	int	i;

	i = 0;
	ret = malloc(len);
	if (ret == NULL)
	{
		if (len > 1)
			free(tab);
		return (NULL);
	}
	while (len > 1 && nb_elem > 0)
	{
		ret[i] = tab[i];
		i++;
		nb_elem--;
	}
	if (len > 0)
		free(tab);
	return (ret);
}

int	*add_fd(t_fd_info *fd, int fd_in)
{
	if (fd->nb_elems == fd->capacity)
	{
		fd->fds = ft_realloc(fd->fds, sizeof(int) * (fd->capacity + 10),
				fd->nb_elems);
		if (fd->fds == NULL)
			return (NULL);
		fd->capacity += 10;
	}
	fd->fds[fd->nb_elems] = fd_in;
	fd->nb_elems++;
	return (fd->fds);
}

void	delete_fd(t_fd_info *fd, int nb_elem)
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

int	dup_fd(t_fd_info *fd, int fd_redirect)
{
	if (fd->nb_elems > 0)
	{
		if (dup2(fd->fds[fd->nb_elems - 1], fd_redirect) == -1)
			return (0);
	}
	return (1);
}

void	close_fd(t_fd_info *fd)
{
	int	i;

	i = 0;
	while (i < fd->nb_elems)
	{
		close(fd->fds[i]);
		i++;
	}
}
