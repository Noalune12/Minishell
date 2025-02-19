#include "minishell.h"

char	*find_home(t_list *env)
{
	int		i;
	t_list	*temp;
	char	*home;

	i = 0;
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

t_list	*find_info_env(t_list **envp, char *content)
{
	t_list	*searched;

	searched = *envp;
	while (searched)
	{
		if (ft_strncmp(searched->content, content, ft_strlen(content)) == 0)
			break ;
		searched = searched->next;
	}
	return (searched);
}

void	update_env(t_list **envp, char *path)
{
	t_list	*env_oldpwd;
	t_list	*env_pwd;

	env_oldpwd = find_info_env(envp, "OLDPWD=");
	env_pwd = find_info_env(envp, "PWD=");
	if (env_oldpwd)
	{
		free(env_oldpwd->content);
		env_oldpwd->content = ft_strjoin("OLDPWD=", env_pwd->content + 4);
	}
	else
		add_node(envp, ft_strjoin("OLDPWD=", env_pwd->content + 4)); //find right place ? + protect
	free(env_pwd->content);
	env_pwd->content = ft_strjoin("PWD=", path); //protect
	free(path);
}

int	ft_cd_home(t_list *envp)
{
	char	*path;

	path = find_home(envp);
	if (!path)
	{
		printf("bash: cd: HOME not set\n");
		return (1);
	}
	printf(YELLOW"Changing directory to HOME: %s\n"RESET, path);
	chdir(path); //protect ?
	update_env(&envp, path);
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
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else
	{
		printf(YELLOW"Changing directory to: %s\n"RESET, cmds[1]);
		if (chdir(cmds[1]) != 0)
		{
			printf(YELLOW"bash: cd: %s: No such file or directory\n"RESET, cmds[1]);
			return (1);
		}
		update_env(&envp, getcwd(NULL, 0)); //protect getcwd ??
	}
	return (0);
}
