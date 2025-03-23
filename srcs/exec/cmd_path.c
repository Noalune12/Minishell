#include "minishell.h"

#include <sys/types.h>
#include <sys/stat.h>

static char	*find_env_path(t_list *envp, t_minishell *minishell)
{
	char	*path_env;
	t_list	*temp;

	path_env = NULL;
	temp = envp;
	while (temp)
	{
		if (ft_strncmp(temp->content, "PATH=", 5) == 0)
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

static char	*join_full_path(t_minishell *minishell, t_path_cmds *path_cmds,
	char **cmds, char **env)
{
	char		*dir;
	char		*full_path;
	struct stat	path;

	dir = ft_strjoin(path_cmds->paths[path_cmds->index], "/");
	if (!dir)
		exit(error_handling_cmd_path(path_cmds, NULL, env, minishell));
	full_path = ft_strjoin(dir, cmds[0]);
	if (!full_path)
		exit(error_handling_cmd_path(path_cmds, dir, env, minishell));
	free(dir);
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) != 0
		&& stat(full_path, &path) == 0 && !S_ISDIR(path.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", cmds[0]);
		perror("");
		free_join_full_path(path_cmds, full_path, env, minishell);
		error_handling_exec(minishell, NULL);
		exit(126);
	}
	if (access(full_path, F_OK | X_OK) == 0 && stat(full_path, &path) == 0
		&& !S_ISDIR(path.st_mode)) //TODO test with exec
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*find_full_path(t_minishell *minishell, t_path_cmds *path_cmds,
	char **cmds, char **env)
{
	char	*full_path;

	path_cmds->paths = ft_split(path_cmds->path_env, ':');
	if (!path_cmds->paths)
	{
		free_tab(env, ft_lstsize(minishell->envp));
		free(path_cmds->path_env);
		exit(error_handling_exec(minishell, "Malloc failed"));
	}
	path_cmds->index = 0;
	while (path_cmds->paths[path_cmds->index])
	{
		full_path = join_full_path(minishell, path_cmds, cmds, env);
		if (full_path)
		{
			ft_free_double(path_cmds->paths);
			return (full_path);
		}
		++path_cmds->index;
	}
	ft_free_double(path_cmds->paths);
	free(full_path);
	return (NULL);
}

char	*find_exec_cmd(char **cmds, t_minishell *minishell, char **env)
{
	char		*full_path;
	t_path_cmds	path_cmds;

	if (ft_strncmp(cmds[0], "./", 2) == 0 || ft_strncmp(cmds[0], "/", 1) == 0)
		exit(free_error_cmd_path(minishell, ERROR_INFILE, env, cmds[0]));
	ft_memset(&path_cmds, 0, sizeof(t_path_cmds));
	path_cmds.path_env = find_env_path(minishell->envp, minishell);
	if (path_cmds.path_env)
	{
		full_path = find_full_path(minishell, &path_cmds, cmds, env);
		free(path_cmds.path_env);
	}
	else
		full_path = NULL;
	if (!full_path)
		exit(free_error_cmd_path(minishell, CMD_NOT_FOUND, env, cmds[0]));
	return (full_path);
}
