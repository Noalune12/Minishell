#include "minishell.h"

char	*find_env_path(t_list *envp, t_minishell *minishell)
{
	char	*path_env;
	t_list	*temp;

	path_env = NULL;
	temp = envp;
	while (temp)
	{
		if (strncmp(temp->content, "PATH=", 5) == 0)
		{
			path_env = ft_strdup(temp->content + 5);
			if (!path_env)
			{
				error_handling_exec(minishell, "Malloc failed");
				exit (1);
			}
			break ;
		}
		temp = temp->next;
	}
	return (path_env);
}

char	*join_full_path(t_minishell *minishell, t_path_cmds *path_cmds,
	char **cmds, int index)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path_cmds->paths[index], "/");
	if (!dir)
	{
		free(path_cmds->path_env);
		ft_free_double(path_cmds->paths);
		error_handling_exec(minishell, "Malloc failed");
		exit (1);
	}
	full_path = ft_strjoin(dir, cmds[0]);
	if (!full_path)
	{
		free(path_cmds->path_env);
		free(dir);
		ft_free_double(path_cmds->paths);
		error_handling_exec(minishell, "Malloc failed");
		exit (1);
	}
	free(dir);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_full_path(t_minishell *minishell, t_path_cmds *path_cmds,
	char **cmds)
{
	char	*full_path;
	size_t	i;

	path_cmds->paths = ft_split(path_cmds->path_env, ':');
	if (!path_cmds->paths)
	{
		free(path_cmds->path_env);
		error_handling_exec(minishell, "Malloc failed");
		exit (1);
	}
	i = 0;
	while (path_cmds->paths[i])
	{
		full_path = join_full_path(minishell, path_cmds, cmds, i);
		if (full_path)
		{
			ft_free_double(path_cmds->paths);
			return (full_path);
		}
		i++;
	}
	ft_free_double(path_cmds->paths);
	free(full_path);
	return (NULL);
}

char	*find_exec_cmd(char **cmds, t_minishell *minishell)
{
	char		*full_path;
	t_path_cmds	path_cmds;

	ft_memset(&path_cmds, 0, sizeof(t_path_cmds));
	path_cmds.path_env = find_env_path(minishell->envp, minishell);
	full_path = find_full_path(minishell, &path_cmds, cmds);
	free(path_cmds.path_env);
	if (!full_path)
	{
		ft_dprintf(STDERR_FILENO, CMD_NOT_FOUND, cmds[0]);
		error_handling_exec(minishell, NULL);
		exit(127);
	}
	return (full_path);
}
