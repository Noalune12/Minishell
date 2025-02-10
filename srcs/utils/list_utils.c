#include "minishell.h"

t_list	*find_env_node(t_list *env, const char *var_searched)
{
	size_t	len;

	len = ft_strlen(var_searched);
	while (env)
	{
		if (ft_strncmp(env->content, var_searched, \
		len) == 0 && env->content[len]  == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}
