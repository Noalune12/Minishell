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

int	open_and_replace(char *filename, t_minishell *minishell)
{
	char	buffer[READ_LEN + 1];
	ssize_t	b_read = 1;
	char	*content = NULL;
	int		fd;
	char	*expanded;

	fd = open(filename, O_RDONLY);
	while (b_read > 0)
	{
		b_read = read(fd, buffer, READ_LEN);
		if (b_read == 0)
			break ;
		if (b_read == -1)
		{
			perror("Failed to read file");
			free(content);
			close(fd);
			return (1);
		}
		buffer[b_read] = '\0';
		if (!content)
			content = ft_strndup(buffer, b_read);
		else
			content = ft_strjoin_free_s1(content, buffer);
		// printf(RED"buffer = %s /// content = %s\n"RESET, buffer, content);
		if (!content)
		{
			perror("Malloc failed");
			close(fd);
			return (1);
		}
	}
	close(fd);
	// printf(GREEN"content = %s\n"RESET, content);
	// printf("env before expand = %s\n", minishell->envp->content);
	expanded = expand_heredoc(content, minishell->envp, minishell);
	// printf(PURPLE"expanded = %s\n"RESET, expanded);
	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror("Failed to open file for writing");
		free(expanded);
		free(content);
		return (1);
	}
	if (write(fd, expanded, ft_strlen(expanded)) == -1)
	{
		perror("Failed to write to file");
		free(expanded);
		free(content);
		close(fd);
		return (1);
	}
	free(expanded);
	free(content);
	close(fd);
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
