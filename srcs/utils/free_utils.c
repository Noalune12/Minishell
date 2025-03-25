#include "minishell.h"

void	close_and_free_fds(t_fd_info *fd)
{
	int	i;

	i = 0;
	while (i < fd->nb_elems)
	{
		close(fd->fds[i]);
		i++;
	}
	free(fd->fds);
}

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

	if (list == NULL)
		return ;
	current = list;
	while (current != NULL)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

void	cleanup_shell(t_minishell *minishell)
{
	close_and_free_fds(&minishell->fds.fd_in);
	close_and_free_fds(&minishell->fds.fd_out);
	if (minishell->envp != NULL)
		free_list(minishell->envp);
	if (minishell->options != NULL)
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
