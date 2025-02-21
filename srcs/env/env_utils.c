#include "minishell.h"

t_list	*find_env_node(t_list *env, const char *var_searched)
{
	size_t	len;

	len = ft_strlen(var_searched);
	while (env)
	{
		if (ft_strncmp(env->content, var_searched, \
		len) == 0 && env->content[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_node(t_list **env, char *content) // nom a changer probablement
{
	t_list	*temp;
	t_list	*new_node;

	temp = *env;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(content);
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}
