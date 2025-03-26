/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:14:40 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:33:04 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_ast		t_ast;
typedef struct s_minishell	t_minishell;
typedef int					(*t_handler)(t_ast *node, t_minishell *minishell);

# define READ_LEN 1000

# define AMBIGUOUS_ERR "minishell: %s: ambiguous redirect\n"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define DOT_ERR "minishell: %s: filename argument required\n"
# define DUP_ERR "Dup failed"
# define DUP2_ERR "Dup2 failed"
# define ERROR_INFILE "minishell: %s: No such file or directory\n"
# define EXECVE_ERR "execve failed"
# define FORK_ERR "fork failed"
# define IS_REDIR "minishell: %s: Is a directory\n"
# define PATH_EQUAL "PATH="
# define PIPE_ERR "pipe failed"
# define SIGQUIT_MESSAGE "Quit (core dumped)\n"
# define SIMPLE_ERR "minishell: %s: "
# define WAIT_ERR "Waitpid failed"

typedef struct s_path_cmds
{
	char	**paths;
	char	*path;
	char	*path_env;
	int		index;
}	t_path_cmds;

typedef struct s_exp_qu
{
	char	**tmp_cmds;
	char	*expanded;
	char	*final;
	char	*temp;
	int		exp;
	int		export;
	int		i;
	int		j;
	int		quote;
}	t_exp_qu;

void	free_tab(char **tab, int i);
void	free_join_full_path(t_path_cmds *path_cmds,	char *str,
			char **env, t_minishell *minishell);

char	**remake_cmds(char **cmds, int *index);
char	*find_exec_cmd(char **cmds, t_minishell *minishell, char **env);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*handle_quotes_exec(char *input);

int		check_cmd(t_ast *node);
int		error_handling_exec(t_minishell *minishell, char *message);
int		exec_minishell(t_ast *node, t_minishell *minishell);
int		expand_quotes_exec(t_ast *node, t_minishell *minishell);
int		handle_and(t_ast *node, t_minishell *minishell);
int		handle_cmd(t_ast *node, t_minishell *minishell);
int		handle_heredocin(t_ast *node, t_minishell *minishell);
int		handle_or(t_ast *node, t_minishell *minishell);
int		handle_pipe(t_ast *node, t_minishell *minishell);
int		handle_redirappend(t_ast *node, t_minishell *minishell);
int		handle_redirin(t_ast *node, t_minishell *minishell);
int		handle_redirout(t_ast *node, t_minishell *minishell);
int		is_builtin(char *cmds);
int		start_as_file(t_ast *node);
int		error_handling_cmd_path(t_path_cmds *path_cmds,	char *str,
			char **env, t_minishell *minishell);
int		free_error_cmd_path(t_minishell *minishell,
			char *message, char **env, char *cmds);

#endif
