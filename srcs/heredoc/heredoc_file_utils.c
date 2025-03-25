#include <fcntl.h>

#include "heredoc.h"
#include "libft.h"
#include "minishell.h"

static void	format_file_name(char *file_name, int fd)
{
	const char		autorized_char[] = AUTORIZED_CHAR;
	unsigned char	index;
	size_t			i;

	i = 0;
	if (read(fd, file_name, RANDOM_NAME_LENGHT - 1) == -1)
	{
		free(file_name);
		return ;
	}
	while (i < RANDOM_NAME_LENGHT - 1)
	{
		index = (unsigned char)file_name[i] % (sizeof(autorized_char) - 1);
		file_name[i] = autorized_char[index];
		i++;
	}
	file_name[i] = '\0';
}

char	*create_temp_file(void)
{
	char	*get_random_name;
	char	*file_name;
	int		fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	get_random_name = malloc(sizeof(char) * RANDOM_NAME_LENGHT);
	if (get_random_name == NULL)
	{
		close(fd);
		return (NULL);
	}
	format_file_name(get_random_name, fd);
	close(fd);
	file_name = ft_strjoin(HEREDOC_PATH_BASE_NAME, get_random_name);
	free(get_random_name);
	if (file_name == NULL)
		return (NULL);
	if (access(file_name, F_OK) == 0)
		return (create_temp_file());
	return (file_name);
}
