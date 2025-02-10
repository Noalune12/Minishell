#include "minishell.h"

// OUTDATED FILE

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free(split);
		split = NULL;
	}
}

void	practice(char *input, t_args *args)
{
	t_args	*current;
	char	**split;
	size_t	i;

	split = ft_split(input, ' ');
	if (!split)
		return ;
	current = args;
	while (current->next)
		current = current->next;
	i = 0;
	while (split[i])
	{
		add_node_test(current);
		current = current->next;
		current->token = i;
		current->arg = ft_strdup(split[i]);
		i++;
	}
	free_split(split);
}
