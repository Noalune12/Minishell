#ifndef HEREDOC_H
# define HEREDOC_H

# define HEREDOC_PATH_BASE_NAME "/tmp/.heredoc_"
# define RANDOM_NAME_LENGHT 10
# define AUTORIZED_CHAR \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

typedef struct s_heredoc
{
	char	*line;
	char	*prompt;
	int		fd;
	int		original_stdin;
}	t_heredoc_utils;

#endif
