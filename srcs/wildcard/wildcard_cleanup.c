#include "minishell.h"

void	cleanup_file_names(char **file_names, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(file_names[i]);
		i++;
	}
	free(file_names);
}

void	free_file_names_array(char **file_names)
{
	int	i;

	i = 0;
	while (file_names[i])
	{
		free(file_names[i]);
		i++;
	}
	free(file_names);
}
