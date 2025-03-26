/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:28 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:22:29 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "libft.h"
#include "minishell.h"

char	*handle_heredoc(char *delimiter)
{
	char	*file_name;
	char	*processed_delimiter;

	processed_delimiter = handle_quotes_exec(delimiter);
	if (processed_delimiter == NULL)
		return (NULL);
	file_name = create_temp_file();
	if (file_name == NULL)
	{
		free(processed_delimiter);
		return (NULL);
	}
	if (write_to_heredoc(file_name, processed_delimiter) == -1)
	{
		free(processed_delimiter);
		free(file_name);
		return (NULL);
	}
	free(processed_delimiter);
	return (file_name);
}

void	handle_regular_heredoc(t_token *current)
{
	char	*tmp_filename;

	tmp_filename = handle_heredoc(current->content);
	if (tmp_filename)
		unlink(tmp_filename);
	free(tmp_filename);
}

int	handle_last_heredoc(t_token *current, int *error)
{
	char	*filename;
	bool	should_expand;

	should_expand = check_expand(current->content);
	filename = handle_heredoc(current->content);
	if (filename == NULL)
	{
		*error = -1;
		return (0);
	}
	current->to_expand = should_expand;
	free(current->content);
	current->content = filename;
	return (1);
}
