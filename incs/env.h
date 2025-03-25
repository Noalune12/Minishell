#ifndef ENV_H
# define ENV_H

# include "types.h"

# define SHLVL_TOO_HIGH	\
			"minishell: warning: shell level (%d) too high, resetting to 1\n"

typedef struct s_shlvl
{
	t_list	*shlvl_node;
	char	*next_lvl;
	int		shlvl;
}	t_shlvl;

t_list	*env_init(char **envp);
t_list	*find_env_node(t_list *env, const char *var_searched);
t_list	*add_node(t_list **env, char *content);

void	free_list(t_list *list);
void	update_pwd(t_list **env);
void	update_shlvl(t_list *env);
void	add_manpath_to_env(t_list **env);

char	*ft_getenv(char *var_name, t_list *env);

int		add_or_replace_env(char *content, t_list **env, int len, int add);

#endif
