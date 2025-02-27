#include "minishell.h"

#include <string.h>
#include <stdlib.h>

#define AUTORIZED_CHAR \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

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
	if (!get_random_name)
	{
		close(fd);
		return (NULL);
	}
	format_file_name(get_random_name, fd);
	if (!get_random_name)
		return (NULL);
	close(fd);
	file_name = ft_strjoin(HEREDOC_PATH_BASE_NAME, get_random_name);
	free(get_random_name);
	if (!file_name)
		return (NULL);
	if (access(file_name, F_OK) == 0)
		return (create_temp_file());
	ft_dprintf(STDERR_FILENO, "%sTEMPORARY PRINTF filename:%s %s\n", RED, RESET, file_name);
	return (file_name);
}

/**
 * @brief Main function to handle heredocs
 *
 * This functions forks once for each heredoc the user has written in
 * his prompt.
 * Creates inside the forks a temporary specific file in /tmp/ depending
 * on the pid value.
 * Has a main loop that uses readline and instead of a classic gnl.
 * Checks with strcmp if the readline returned string matches the delimiter
 * of the current heredoc.
 * Checks if there is environnement variable to expand inside the heredoc line,
 * if there is calls a function that replace the initial value to the expanded value.
 * Writes in the previously created file the line with or without expands.
 * Exit.....
 *
 * A FINIR
 *
 */
// int	temp_main_loop_here_doc_creation(void)
// {
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
//     	char	*file_name = create_temp_file();
// 		char	*line;
//     	int		temp_fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0644);

// 		while (line = readline("> ")) // a changer une fois les tests terminés
// 		{
// 			if (ft_strcmp(line, delimiter /*aka node->next*/) == 0)
// 				break ;
// 			else
// 				write(temp_fd, line, ft_strlen(line)); // remplacer par ft_dprintf (peut ecrire dans nimporte quel fd)
// 			// if (should_expand == true) // appel de fonction qui check si dans line il y a un $, cherche dans env.
// 			// 	write_expanded_line(temp_fd, line); // remplacer line par line avec expand, on a pas besoin du else derriere du coup
// 			free(line);
// 		}
// 		close(temp_fd);
// 		exit(0);
// 	}
// 	else
// 	{
// 		int status;
// 		waitpid(pid, &status, 0); // ca degage ?
// 	}
// 	// return un truc ou pas ? int j'imagine pour les retours d'erreurs de nos sous-fonctions
// }

// int	main(void)
// {
// 	char		*temp_file;
// 	pid_t		pid;
// 	int			i;
// 	static int	nb_children = 50;

// 	printf("Parent PID: %d\n", getpid());
// 	for (i = 0; i < nb_children; i++)
// 	{
// 		pid = fork();
// 		if (pid < 0) {
// 			perror("Fork failed");
// 			exit(1);
// 		}
// 		if (pid == 0)
// 		{
// 			temp_file = create_temp_file();
// 			printf("%sChild %d file_name: %s%s\n", GREEN, i+1, temp_file, RESET);
// 			free(temp_file);
// 			exit(0);
// 		}
// 	}
// 	temp_file = create_temp_file();
// 	printf("%sParent file_name: %s%s\n", RED, temp_file, RESET);
// 	free(temp_file);
// 	for (i = 0; i < nb_children; i++)
// 		wait(NULL);
// 	return (0);
// }


/*

cat << EOF && export test="TEST" && cat << EOF

Dans ce cas, si on appelle $test dans le premier heredoc, l'export n'a pas encore ete fait
On essayera de faire lexpand dans le fichier mais rien n'en resortira.
Neanmoins dans le 2e heredoc lexport a ete fait et il faudra faire lexpand a nouveau, le fichier contiendra donc TEST


*/
