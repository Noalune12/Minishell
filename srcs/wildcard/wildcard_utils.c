#include <dirent.h>

#include "minishell.h"
#include "wildcard.h"

bool	contain_wildcard(char *token)
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
		else if (token[i] == '\"' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (token[i] == '*' && !in_dquotes && !in_squotes)
			return (true);
		i++;
	}
	return (false);
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
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (wildcard_match(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char	**allocate_2d_array(int count)
{
	char	**array;

	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	array[count] = NULL;
	return (array);
}

bool	should_include_file(char *pattern, char *filename)
{
	if (filename[0] == '.' && pattern[0] != '.')
		return (false);
	return (wildcard_match(pattern, filename));
}
