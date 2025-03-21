#include "../../incs/minishell.h"

typedef struct s_env
{
	char	*content;
	struct s_env	*next;
} t_env;

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
