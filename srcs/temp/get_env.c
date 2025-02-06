#include "../../incs/minishell.h"

typedef struct s_env
{
	char	*content;
	struct s_env	*next;
} t_env;

void add_node(t_env **env, char *content)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return;
	new_node->content = ft_strdup(content); //protect
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

t_env	*ft_get_env(char **envp)
{
	int	i;
	t_env	*env;

	i = 0;
	env = NULL;
	if (!envp[i])
	{
		env = malloc(sizeof(t_env));
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


// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	env = ft_get_env(envp);
// 	print_env(env);
// 	free_env(env);
// }
