#include "minishell.h"

void	free_token_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
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

void	free_env(t_minishell *minishell)
{
	if (minishell->envp)
		free_list(minishell->envp);
	if (minishell->options) // a deplacer
		free(minishell->options);
	minishell->envp = NULL;
	minishell->token = NULL;
}

char	**ft_free_double(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free (strs);
		strs = NULL;
	}
	return (NULL);
}
