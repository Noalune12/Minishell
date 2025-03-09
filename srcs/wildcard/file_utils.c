#include <dirent.h>

#include "minishell.h"
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

static int	get_file_names_setup(char ***file_names, int *count, DIR **dir)
{
	*file_names = allocate_2d_array(*count);
	*dir = opendir(".");
	if (!(*file_names) || !*(dir))
	{
		if (*file_names)
			free(*file_names);
		return (-1);
	}
	return (1);
}

bool	add_filename(char **filenames, char *name, int index)
{
	filenames[index] = ft_strdup(name);
	if (!filenames[index])
		return (false);
	return (true);
}

char	**get_file_names(char *pattern, int count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**file_names;
	int				i;

	if (get_file_names_setup(&file_names, &count, &dir) == -1)
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (entry && i < count)
	{
		if (should_include_file(pattern, entry->d_name))
		{
			if (!add_filename(file_names, entry->d_name, i++))
			{
				cleanup_file_names(file_names, i - 1);
				closedir(dir);
				return (NULL);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	sort_file_names(file_names, count);
	return (file_names);
}
