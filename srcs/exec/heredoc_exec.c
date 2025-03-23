#include "minishell.h"

#define READ_LEN 1000

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
		res[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

static int	error_handling_heredoc(char *filename, char *str, int fd)
{
	if (filename)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", filename);
		perror("");
	}
	else
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
	if (str)
		free(str);
	if (fd != -1)
		close(fd);
	return (1);
}

static int	get_content(int fd, char **content, char *filename)
{
	char	buffer[READ_LEN + 1];
	ssize_t	b_read;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, READ_LEN);
		if (b_read == 0)
			break ;
		if (b_read == -1)
			return (error_handling_heredoc(filename, *content, fd));
		buffer[b_read] = '\0';
		if (!*content)
			*content = ft_strndup(buffer, b_read);
		else
			*content = ft_strjoin_free_s1(*content, buffer);
		if (!content)
			return (error_handling_heredoc(NULL, NULL, fd));
	}
	return (0);
}

static int	write_in_heredoc(char *filename, char *expanded)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (error_handling_heredoc(filename, expanded, -1));
	if (write(fd, expanded, ft_strlen(expanded)) == -1)
		return (error_handling_heredoc(filename, expanded, fd));
	free(expanded);
	close(fd);
	return (0);
}

static int	open_and_replace(char *filename, t_minishell *minishell)
{
	char	*content;
	int		fd;
	char	*expanded;

	content = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", filename);
		perror("");
		return (1);
	}
	if (get_content(fd, &content, filename) == 1)
		return (1);
	close(fd);
	expanded = expand_heredoc(content, minishell);
	free(content);
	if (!expanded)
		return (error_handling_heredoc(NULL, NULL, -1));
	if (write_in_heredoc(filename, expanded) == 1)
		return (1);
	return (0);
}

int	handle_heredocin(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	if (node->cmd->to_expand == true)
	{
		if (open_and_replace(node->cmd->cmds[0], minishell) == 1)
			return (1);
	}
	fd = open(node->cmd->cmds[0], O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	if (add_fd(&minishell->fds.fd_in, fd) == NULL)
	{
		close(fd);
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_in, minishell->fds.fd_in.nb_elems - 1);
	close(fd);
	return (ret);
}
