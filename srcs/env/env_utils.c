#include "minishell.h"

t_list	*find_env_node(t_list *env, const char *var_searched)
{
	size_t	len;

	len = ft_strlen(var_searched);
	while (env)
	{
		if (ft_strncmp(env->content, var_searched, len) == 0 \
			&& env->content[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

static t_list	*error_handling(t_list	*new_node)
{
	if (new_node != NULL)
		free(new_node);
	ft_dprintf(STDERR_FILENO, "Malloc failed\n");
	return (NULL);
}

t_list	*add_node(t_list **env, char *content) // nom a changer probablement + retour derreur
{
	t_list	*temp;
	t_list	*new_node;

	temp = *env;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (error_handling(NULL));
	new_node->content = ft_strdup(content);
	if (new_node->content == NULL)
		return (error_handling(new_node));
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return (new_node);
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (new_node);
}
