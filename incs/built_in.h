/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:12:45 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:54:31 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

typedef struct s_minishell	t_minishell;
typedef struct s_ast		t_ast;
typedef struct s_list		t_list;
typedef int					(*t_builtin)(char **cmds, t_minishell *minishell);

# define CD_HOME "minishell: cd: HOME not set\n"
# define DOUBLE_STR_ERR "minishell: %s: %s: "
# define EXIT_ERROR "minishell: exit: %s: numeric argument required\n"
# define EXPORT_ERROR "minishell: export: `%s': not a valid identifier\n"
# define OLDPWD_NOT_SET "minishell: cd: OLDPWD not set\n"
# define PWD_ERROR "minishell: pwd: %s: invalid option\npwd: usage: pwd\n"
# define TOO_MANY_ARGS "minishell: %s: too many arguments\n"
# define CWD_ERROR \
	"%s: error retrieving current directory: \
getcwd: cannot access parent directories: "

# define CD				"cd"
# define ECHO			"echo"
# define ENV			"env"
# define EXIT			"exit"
# define EXPORT			"export"
# define OPTIONS_BI		"options"
# define PTOKENS_BI		"ptokens"
# define PTREE_BI		"ptree"
# define PWD_BI			"pwd"
# define UNSET			"unset"

# define OLDPWD			"OLDPWD"
# define OLDPWD_EQUAL	"OLDPWD="
# define PWD			"PWD"
# define PWD_EQUAL		"PWD="
# define HOME_EQUAL		"HOME="

void	ft_list_sort(t_list **begin_list, int (*cmp)(char *, char *));
void	swap_strs(char **s1, char **s2);

int		add_export_to_env(char *cmds, t_list **env);
int		add_or_append_env(char *content, t_list **env, int len);
int		ascii_cmp(char *a, char *b);
int		check_export(char **cmds);
int		find_env_var_node(char *var, t_list **env);
int		ft_cd(char **cmds, t_minishell *minishell);
int		ft_echo(char **cmds, t_minishell *minishell);
int		ft_exit(char **cmds, t_minishell *minishell);
int		ft_export(char **cmds, t_minishell *minishell);
int		ft_pwd(char **cmds, t_minishell *minishell);
int		ft_strnlen(char *str, char c);
int		ft_unset(char **cmds, t_minishell *minishell);
int		handle_builtin(t_ast *node, t_minishell *minishell);
int		remove_node(t_list **head, char *var);
int		update_cd_env(t_list **envp, char *path, int to_home);

t_list	*copy_env(t_list *env);

#endif
