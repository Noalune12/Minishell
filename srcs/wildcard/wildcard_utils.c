#include "minishell.h"

#include <dirent.h>

bool	contains_wildards(char *token)
{
	bool	in_squotes;
	bool	in_dquotes;
	size_t	i;

	if (!token)
		return (false);
	in_squotes = false;
	in_dquotes = false;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		else if (token[i] == '\'' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (token[i] = '*' && !in_dquotes && !in_squotes)
			return (true);
		i++;
	}
	return (false);
}

void	swap_files(char **first_file, char **second_file)
{
	char	*tmp;

	tmp = *first_file;
	*first_file = *second_file;
	*second_file = tmp;
}

void	sort_file_names(char **file_names, int count)
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

int	count_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == "." && pattern[0] != ".") // check des fichiers cachés : si le fichier actuel est 
			continue ;
		if (wildcard_matches(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}
