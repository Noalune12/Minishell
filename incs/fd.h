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

void	delete_fd(t_fd_info *fd, int nb_elem);
void	close_fd(t_fd_info *fd);
void	close_and_free_fds(t_fd_info *fd);

int		*add_fd(t_fd_info *fd, int fd_in);
int		dup_fd(t_fd_info *fd, int fd_redirect);

#endif
