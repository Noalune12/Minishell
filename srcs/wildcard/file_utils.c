/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:04 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:21:49 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wildcard.h"

static void	swap_files(char **first_file, char **second_file)
{
	char	*tmp;

	tmp = *first_file;
	*first_file = *second_file;
	*second_file = tmp;
}

static void	sort_file_names(char **file_names, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(file_names[i], file_names[j]) > 0)
				swap_files(&file_names[i], &file_names[j]);
			j++;
		}
		i++;
	}
}

static bool	get_file_names_setup(t_wildcard *data, int count)
{
	data->file_names = allocate_2d_array(count);
	data->dir = opendir(CURRENT_DIR);
	if (data->file_names == NULL || data->dir == NULL)
	{
		if (data->file_names != NULL)
		{
			free(data->file_names);
			data->file_names = NULL;
		}
		if (data->dir != NULL)
			closedir(data->dir);
		return (false);
	}
	data->entry = readdir(data->dir);
	if (data->entry == NULL)
	{
		if (data->file_names)
			free(data->file_names);
		if (data->dir)
			closedir(data->dir);
		return (false);
	}
	return (true);
}

static void	cleanup_resources(t_wildcard *data)
{
	int	i;

	if (data->file_names)
	{
		i = 0;
		while (data->file_names[i])
		{
			free(data->file_names[i]);
			i++;
		}
		free(data->file_names);
	}
	if (data->dir)
		closedir(data->dir);
}

char	**get_file_names(char *pattern, int count)
{
	t_wildcard	d;

	ft_memset(&d, 0, sizeof(t_wildcard));
	if (get_file_names_setup(&d, count) == false)
		return (NULL);
	while (d.i < count)
	{
		d.entry = readdir(d.dir);
		if (d.entry == NULL)
			break ;
		if (should_include_file(pattern, d.entry->d_name) == true)
		{
			if (add_filename(d.file_names, d.entry->d_name, d.i++) == false)
			{
				cleanup_resources(&d);
				return (NULL);
			}
		}
	}
	sort_file_names(d.file_names, d.i);
	d.file_names[d.i] = NULL;
	closedir(d.dir);
	return (d.file_names);
}
