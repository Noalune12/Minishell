#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>

# include "options.h"


# include "fd.h" // cannot include it otherwise --> error
# include "types.h" // je crois lui aussi on peut pas faire autrement


extern int	g_signal_received;

typedef struct s_token
{
	char			*content;
	bool			to_expand;
	t_node_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	char		*exec;
	char		*input;
	bool		exec_status;
	int			exit_status;
	int			is_pipe;
	pid_t		pid;
	int			fd_in;
	int			fd_out;
	t_options	*options;
	t_list		*envp;
	t_token		*token;
	t_ast		*ast_node;
	t_fds		fds;
}	t_minishell;

void	split_operators(t_minishell *minishell);
void	tokenize_input(t_minishell *minishell);
void	syntax_check(t_minishell *minishell);
void	minishell_main_loop(t_minishell *minishell);
void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);

char	*read_input(t_minishell *minishell);

#endif
