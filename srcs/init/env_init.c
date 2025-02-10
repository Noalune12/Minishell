#include "minishell.h"

// t_list	*split_env(char **envp)
// {
// 	t_list	*returned_env;
// 	char	**split;
// 	size_t	i;

// 	if (envp == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		split = ft_split(envp, '='); // define '=' ? (maybe need '+=' define aswell)
// 		if (!split)
// 			return (NULL); // lstclear env ?
// 	}
// }

static void add_node(t_list **env, char *content)
{
	t_list	*temp;
	t_list	*new_node;

	temp = *env;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return;
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
		return;
	}
	while (temp->next)
			temp = temp->next;
	temp->next = new_node;
}

void	free_list(t_list *list)
{
	t_list	*current;
	t_list	*next;

	if (!list)
		return ;
	current = list;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

static void	print_env(t_list *env)
{
	t_list	*temp;

	if (!env)
		return ;
	temp = env;
	while (temp)
	{
		if (temp->content)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

static t_list	*ft_get_env(char **envp)
{
	int		i;
	t_list	*env;

	i = 0;
	env = NULL;
	if (!envp[i])
	{
		env = malloc(sizeof(t_list));
		if (!env)
			return (NULL);
		env->content = NULL;
		env->next = NULL;
		return (env);
	}
	while (envp[i])
	{
		add_node(&env, envp[i]);
		i++;
	}
	return (env);
}

t_list	*env_init(char **envp)
{
	t_list	*set_up_env;

	set_up_env = ft_get_env(envp); // yours
	update_shlvl(set_up_env);
	print_env(set_up_env);
	if (nested_shell(set_up_env))
		update_shlvl(set_up_env);
	// set_up_env = split_env(envp); // mine
	// if (!set_up_env)
	// 	return (NULL);
	print_env(set_up_env);
	return (set_up_env);
}
