#include <dirent.h>

#include "ast.h"
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
	t_wildcard	data;

	ft_memset(&data, 0, sizeof(t_wildcard));
	data.dir = opendir(CURRENT_DIR);
	if (data.dir != NULL)
		data.entry = readdir(data.dir);
	while (data.entry != NULL)
	{
		if (data.entry->d_name[0] == '.' && pattern[0] != '.')
		{
			data.entry = readdir(data.dir);
			continue ;
		}
		if (wildcard_match(pattern, data.entry->d_name))
		data.count++;
		data.entry = readdir(data.dir);
	}
	if (data.dir != NULL)
		closedir(data.dir);
	return (data.count);
}

char	**allocate_2d_array(int count)
{
	char	**array;

	array = malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
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

bool	add_filename(char **filenames, char *name, int index)
{
	(void) name;
	filenames[index] = ft_strdup(name);
	if (filenames[index] == NULL)
		return (false);
	return (true);
}
