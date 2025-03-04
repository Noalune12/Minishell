#include "minishell.h"

char	*find_home(t_list *env)
{
	t_list	*temp;
	char	*home;

	temp = env;
	home = NULL;
	if (!(temp->content))
		return (NULL);
	while (temp)
	{
		if (ft_strncmp(temp->content, "HOME=", 5) == 0)
		{
			home = temp->content + 5;
			break ;
		}
		temp = temp->next;
	}
	return (home);
}

t_list	*find_info_env(t_list **envp, char *content, int equal)
{
	t_list	*searched;

	searched = *envp;
	if (equal == 1)
	{
		while (searched)
		{
			if (ft_strncmp(searched->content, content, ft_strlen(content)) == 0)
				break ;
			searched = searched->next;
		}
	}
	else
	{
		while (searched)
		{
			if (ft_strcmp(searched->content, content) == 0)
				break ;
			searched = searched->next;
		}
	}
	return (searched);
}

void	update_env(t_list **envp, char *path, int to_home) // if PWD is unset what to do ???
{
	t_list	*env_oldpwd;
	t_list	*env_pwd;

	env_oldpwd = find_info_env(envp, "OLDPWD=", 1);
	if (!env_oldpwd)
		env_oldpwd = find_info_env(envp, "OLDPWD", 0);
	env_pwd = find_info_env(envp, "PWD=", 1);
	if (!env_pwd)
		env_pwd = find_info_env(envp, "PWD", 0);
	if (env_oldpwd && env_pwd)
	{
		free(env_oldpwd->content);
		env_oldpwd->content = ft_strjoin("OLDPWD=", env_pwd->content + 4); //protect
	}
	else if (!env_oldpwd && env_pwd)
		add_node(envp, ft_strjoin("OLDPWD=", env_pwd->content + 4)); //find right place ? + protect
	else
		remove_node(envp, "OLDPWD"); //protect
	if (env_pwd)
	{
		free(env_pwd->content);
		env_pwd->content = ft_strjoin("PWD=", path); //protect
	}
	else
		add_node(envp, ft_strjoin("PWD=", path)); //protect
	if (!to_home)
		free(path);
}

static int	ft_cd_home(t_list *envp)
{
	char	*path;

	path = find_home(envp);
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, CD_HOME);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_dprintf(STDERR_FILENO, "chdir failed\n");
		free(path);
		return (1);
	}
	update_env(&envp, path, 1);
	return (0);
}

static int	ft_cd_path(char **cmds, t_list **envp)
{
	char	*cwd;

	if (chdir(cmds[1]) != 0)
	{
		ft_dprintf(STDERR_FILENO, FILE_NOT_FOUND, "cd", cmds[1]);
		return (1);
	}
	cwd = getcwd(NULL, 4094);
	if (!cwd)
	{
		ft_dprintf(STDERR_FILENO, "getcwd failed\n");
		return (1);
	}
	update_env(envp, cwd, 0);
	return (0);
}

int	ft_cd(char **cmds, t_list *envp)
{
	if (!cmds[1])
	{
		if (ft_cd_home(envp) == 1)
			return (1);
	}
	else if (cmds[2])
	{
		ft_dprintf(STDERR_FILENO, TOO_MANY_ARGS, "cd");
		return (1);
	}
	else
	{
		if (ft_cd_path(cmds, &envp) == 1)
			return (1);
	}
	return (0);
}
