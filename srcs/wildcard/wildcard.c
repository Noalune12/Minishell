/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:56 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:20:57 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "wildcard.h"

static bool	replace_for_expanded_filename(t_token *current, char **file_names)
{
	t_token	*last;
	int		i;

	if (file_names[0] == NULL)
		return (true);
	free(current->content);
	current->content = ft_strdup(file_names[0]);
	if (current->content == NULL)
		return (false);
	i = 1;
	last = current;
	while (file_names[i] != NULL)
	{
		if (add_token_in_place(&last, file_names[i], NODE_COMMAND) == false)
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
	ft_free_double(file_names);
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
