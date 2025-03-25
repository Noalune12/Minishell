#ifndef EXEC_H
# define EXEC_H

# define DUP2_ERR "Dup2 failed"
# define DUP_ERR "Dup failed"
# define EXECVE_ERR "execve failed"
# define FORK_ERR "fork failed"
# define WAIT_ERR "Waitpid failed"
# define PIPE_ERR "pipe failed"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define DOT_ERR "minishell: %s: filename argument required\n"
# define SIMPLE_ERR "minishell: %s: "
# define SIGQUIT_MESSAGE "Quit (core dumped)\n"
# define PATH_EQUAL "PATH="
# define ERROR_INFILE "minishell: %s: No such file or directory\n"
# define IS_REDIR "minishell: %s: Is a directory\n"

typedef struct s_minishell	t_minishell;
typedef struct s_ast		t_ast;
typedef int					(*t_handler)(t_ast *node, t_minishell *minishell);

typedef struct s_path_cmds
{
	char	*path;
	char	**paths;
	char	*path_env;
	int		index;
}	t_path_cmds;

typedef struct s_exp_qu
{
	char	*expanded;
	char	*temp;
	char	*final;
	char	**tmp_cmds;
	int		exp;
	int		quote;
	int		i;
	int		j;
}	t_exp_qu;

void	free_tab(char **tab, int i);
void	free_join_full_path(t_path_cmds *path_cmds,	char *str,
			char **env, t_minishell *minishell);

int		error_handling_exec(t_minishell *minishell, char *message);
int		is_builtin(char *cmds);
int		start_as_file(t_ast *node);
int		exec_minishell(t_ast *node, t_minishell *minishell);
int		expand_quotes_exec(t_ast *node, t_minishell *minishell);
int		handle_cmd(t_ast *node, t_minishell *minishell);
int		check_cmd_content(t_ast *node);
int		check_cmd(t_ast *node);
int		error_handling_cmd_path(t_path_cmds *path_cmds,	char *str,
			char **env, t_minishell *minishell);
int		free_error_cmd_path(t_minishell *minishell,
			char *message, char **env, char *cmds);
int		handle_and(t_ast *node, t_minishell *minishell);
int		handle_or(t_ast *node, t_minishell *minishell);
int		handle_pipe(t_ast *node, t_minishell *minishell);
int		handle_redirin(t_ast *node, t_minishell *minishell);
int		handle_heredocin(t_ast *node, t_minishell *minishell);
int		handle_redirout(t_ast *node, t_minishell *minishell);
int		handle_redirappend(t_ast *node, t_minishell *minishell);

char	*handle_quotes_exec(char *input);
char	*find_exec_cmd(char **cmds, t_minishell *minishell, char **env);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	**remake_cmds(char **cmds, int *index);

#endif
