#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h" // a enlever pour mettre au propre

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

t_token *find_last_heredoc(t_token *start, t_token **last_heredoc);

void	handle_regular_heredoc(t_token *current);

char	*create_temp_file(void);
char	*handle_heredoc(char *delimiter);

bool	check_expand(char *delimiter);

int		check_heredoc(t_minishell *minishell);
int		handle_last_heredoc(t_token *current, int *error);
int		is_last_heredoc(t_token *current, t_token *last_heredoc);
int		is_op(char *token);
int		is_valid_heredoc_delimiter(char *token);
int		write_to_heredoc(char *file_name, char *delimiter);

#endif
