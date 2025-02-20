#include "minishell.h"

char	**ft_free_double(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free (strs);
		strs = NULL;
	}
	return (NULL);
}

char	*find_env_path(t_list *envp)
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
				// error_handler(errno, "strdup failed", cmds);
			break ;
		}
		temp = temp->next;
	}
	// if (!path_env)
		// error_handler(errno, "PATH not defined in the envp", cmds);
	return (path_env);
}

char	*join_full_path(char *path, char **cmds, char **paths, char *path_env)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path, "/");
	if (!dir)
	{
		free(path_env);
		ft_free_double(paths);
		//error_handler(ENOMEM, "Strjoin failed", cmds);
	}
	full_path = ft_strjoin(dir, cmds[0]);
	if (!full_path)
	{
		free(path_env);
		free(dir);
		ft_free_double(paths);
		//error_handler(ENOMEM, "Strjoin failed", cmds);
	}
	free(dir);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_full_path(char **cmds, char *path_env)
{
	char	*full_path;
	char	**paths;
	size_t	i;

	paths = ft_split(path_env, ':');
	if (!paths)
	{
		free(path_env);
		//error_handler(errno, "Split failed", cmds);
	}
	i = 0;
	while (paths[i])
	{
		full_path = join_full_path(paths[i], cmds, paths, path_env);
		if (full_path)
		{
			ft_free_double(paths);
			return (full_path);
		}
		i++;
	}
	ft_free_double(paths);
	free(full_path);
	return (NULL);
}

char	*find_exec_cmd(char **cmds, t_list *envp)
{
	char	*full_path;
	char	*path_env;

	path_env = find_env_path(envp);
	full_path = find_full_path(cmds, path_env);
	free(path_env);
	if (!full_path)
	{
		ft_free_double(cmds);
		exit(127);
	}
	return (full_path);
}
