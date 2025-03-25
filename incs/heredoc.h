#ifndef HEREDOC_H
# define HEREDOC_H

# include <stdbool.h>

# include "types.h"

# define AND 				"&&"
# define APPEND				">>"
# define CLOSE_PAR			")"
# define HEREDOC			"<<"
# define OPEN_PAR			"("
# define OR					"||"
# define PIPE				"|"
# define REDIRIN			"<"
# define REDIROUT			">"

# define DQUOTES			"\"\""
# define SQUOTES			"''"

# define HEREDOC_PATH_BASE_NAME "/tmp/.heredoc_"
# define RANDOM_NAME_LENGHT 10
# define AUTORIZED_CHAR \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
# define HEREDOC_ERROR_MESSAGE \
	"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"

extern int	g_signal_received;

typedef struct s_heredoc
{
	char	*line;
	char	*prompt;
	int		fd;
	int		original_stdin;
}	t_heredoc_utils;

t_token	*find_last_heredoc(t_token *start, t_token **last_heredoc);

void	handle_regular_heredoc(t_token *current);
void	check_heredoc(t_minishell *minishell);

char	*create_temp_file(void);
char	*handle_heredoc(char *delimiter);
char	*handle_quotes_exec(char *input);

bool	check_expand(char *delimiter);

int		handle_last_heredoc(t_token *current, int *error);
int		is_last_heredoc(t_token *current, t_token *last_heredoc);
int		is_op(char *token);
int		is_valid_heredoc_delimiter(char *token);
int		write_to_heredoc(char *file_name, char *delimiter);

#endif
