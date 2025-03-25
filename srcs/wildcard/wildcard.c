#include "minishell.h"
#include "wildcard.h"

static bool	replace_for_expanded_filename(t_token *current, char **file_names)
{
	t_token	*last;
	int		i;

	if (!file_names[0])
		return (true);
	free(current->content);
	current->content = ft_strdup(file_names[0]);
	if (!current->content)
		return (false);
	i = 1;
	last = current;
	while (file_names[i])
	{
		if (!add_token_in_place(&last, file_names[i], NODE_COMMAND))
			return (false);
		last = last->next;
		i++;
	}
	return (true);
}

static bool	expand_token_wildcard(t_token *current)
{
	char	**file_names;
	int		count_found_files;
	bool	res;

	count_found_files = 0;
	if (current == NULL || current->content == NULL)
		return (false);
	count_found_files = count_matches(current->content);
	if (count_found_files == -1)
		return (false);
	file_names = get_file_names(current->content, count_found_files);
	if (file_names == NULL)
		return (false);
	res = replace_for_expanded_filename(current, file_names);
	free_file_names_array(file_names);
	return (res);
}

void	expand_wildcards(t_minishell *minishell)
{
	t_token	*current;
	t_token	*next;

	if (minishell->token == NULL || minishell->exec_status == false)
		return ;
	current = minishell->token;
	while (current != NULL)
	{
		next = current->next;
		if (current->type == NODE_COMMAND && contain_wildcard(current->content))
		{
			if (expand_token_wildcard(current) == false)
			{
				minishell->exec_status = false;
				return ;
			}
			current = next;
		}
		current = next;
	}
}
