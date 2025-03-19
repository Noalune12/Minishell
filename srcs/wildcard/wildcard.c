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

	if (!current || !current->content)
		return (false);
	count_found_files = count_matches(current->content);
	if (count_found_files == 0)
		return (true);
	file_names = get_file_names(current->content, count_found_files);
	if (!file_names)
		return (false);
	res = replace_for_expanded_filename(current, file_names);
	free_file_names_array(file_names);
	return (res);
}

t_token	*expand_wildcards(t_token *tokens, bool *exec_status)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || *exec_status == false)
		return (NULL);
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == NODE_COMMAND && contain_wildcard(current->content))
		{
			if (!expand_token_wildcard(current))
			{
				free_token_list(tokens);
				*exec_status = false;
				return (NULL);
			}
			current = next;
		}
		current = next;
	}
	return (tokens);
}
