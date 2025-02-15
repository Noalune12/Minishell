#include "minishell.h"

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

void	free_env(t_minishell *minishell)
{
	if (minishell->envp)
		free_list(minishell->envp);
	if (minishell->token)
		free_list(minishell->token);
}

// void	free_split(char **split)
// {
// 	size_t	i;

// 	i = 0;
// 	if (split)
// 	{
// 		while (split[i])
// 		{
// 			free(split[i]);
// 			split[i] = NULL;
// 			i++;
// 		}
// 		free(split);
// 		split = NULL;
// 	}
// }
