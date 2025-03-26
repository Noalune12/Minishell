/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:15:33 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:15:34 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H

typedef struct s_fd_info
{
	int		*fds;
	int		nb_elems;
	int		capacity;
}	t_fd_info;

typedef struct s_fds
{
	t_fd_info	fd_in;
	t_fd_info	fd_out;
}	t_fds;

void	close_and_free_fds(t_fd_info *fd);
void	close_fd(t_fd_info *fd);
void	delete_fd(t_fd_info *fd, int nb_elem);

int		*add_fd(t_fd_info *fd, int fd_in);
int		dup_fd(t_fd_info *fd, int fd_redirect);

#endif
