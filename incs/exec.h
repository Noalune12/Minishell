#ifndef EXEC_H
# define MINISHELL_H

typedef struct s_minishell		t_minishell;
typedef struct s_ast			t_ast;

typedef int (* t_handler)(t_ast *node, t_minishell *minishell);

typedef struct s_path_cmds
{
	char	*path;
	char	**paths;
	char	*path_env;
	int		index;
}	t_path_cmds;

typedef struct	s_exp_qu
{
	char	*expanded;
	char	*temp;
	char	*final;
	int		exp;
	int		quote;
	int		i;
	int		j;
}	t_exp_qu;

int		error_handling_exec(t_minishell *minishell, char *message);
int		is_builtin(char *cmds);
void	free_tab(char **tab, int i);
int		start_as_file(t_ast *node);

int		exec_minishell(t_ast *node, t_minishell *minishell);

int		expand_quotes_exec(t_ast *node, t_minishell *minishell);
char	*handle_quotes_exec(char *input);

int		handle_cmd(t_ast *node, t_minishell *minishell);
char	*find_exec_cmd(char **cmds, t_minishell *minishell, char **env);
int		check_cmd_content(t_ast *node);
int		check_cmd(t_ast *node);
void	free_join_full_path(t_path_cmds *path_cmds,	char *str,
			char **env, t_minishell *minishell);
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
char	*ft_strjoin_free_s1(char *s1, char *s2);

char	**ft_free_double(char **strs);

#endif
