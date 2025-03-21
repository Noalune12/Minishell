#include "../../incs/minishell.h"

typedef struct s_env
{
	char	*content;
	struct s_env	*next;
} t_env;

// t_list	*add_node(t_list **env, char *content)
// {
// 	t_list	*temp;
// 	t_list	*new_node;

// 	if (!env)
// 		return (NULL);
// 	temp = *env;
// 	new_node = malloc(sizeof(t_list));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->content = ft_strdup(content);
// 	if (!new_node->content)
// 	{
// 		free(new_node);
// 		return (NULL);
// 	}
// 	new_node->next = NULL;
// 	if (!*env)
// 	{
// 		*env = new_node;
// 		return (new_node);
// 	}
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_node;
// 	return (new_node);
// }

void	free_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return;
	temp = env;
	while (temp)
	{
		temp = env->next;
		if (env->content)
			free(env->content);
		free(env);
		env = temp;
	}
}

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s", temp->content);
		temp = temp->next;
	}
}
