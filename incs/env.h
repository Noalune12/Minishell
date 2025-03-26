/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:13:59 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:58:15 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_list		t_list;

# define SHLVL_TOO_HIGH	\
			"minishell: warning: shell level (%d) too high, resetting to 1\n"

typedef struct s_shlvl
{
	t_list	*shlvl_node;
	char	*next_lvl;
	int		shlvl;
}	t_shlvl;

t_list	*add_node(t_list **env, char *content);
t_list	*env_init(char **envp);
t_list	*find_env_node(t_list *env, const char *var_searched);

void	add_manpath_to_env(t_list **env);
void	free_list(t_list *list);
void	update_pwd(t_list **env);
void	update_shlvl(t_list *env);

int		add_or_replace_env(char *content, t_list **env, int len, int add);

#endif
