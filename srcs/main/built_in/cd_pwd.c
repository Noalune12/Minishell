#include "../../../incs/minishell.h"

void	update_env(t_list **envp, char *path)
{
	t_list	*env_oldpwd;
	t_list	*env_pwd;

	env_oldpwd = *envp;
	while (env_oldpwd)
	{
		if (strcmp(env_oldpwd->content, "OLDPWD=\0") == 0)
			break ;
		env_oldpwd = env_oldpwd->next;
	}
	env_pwd = *envp;
	while (env_pwd)
	{
		if (strcmp(env_pwd->content, "PWD=\0") == 0)
			break ;
		env_pwd = env_pwd->next;
	}
	// OLDPWD become PWD
	free(env_oldpwd->content);
	env_oldpwd->content = ft_strjoin("OLDPWD=", env_pwd->content + 4);
	// PWD become path
	free(env_pwd->content);
	env_pwd->content = ft_strjoin("PWD=", path);
}

int	ft_cd(char *input, t_list *envp)
{
	int		i;
	char	*path;

	i = 2;

	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
	{
		path = find_home(envp);
		if (!path)
		{
			printf(YELLOW"Error: HOME is not defined\n"RESET);
			return (1);
		}
		printf(YELLOW"Changing directory to HOME: %s\n"RESET, path);
		chdir(path); //protect ?
		update_env(&envp, path);
	}
	else
	{
		printf(YELLOW"Changing directory to: %s\n"RESET, input + i);
		if (chdir(input + i) != 0)
		{
			printf(YELLOW"bash: cd: %s: No such file or directory\n"RESET, input + i);
			return (1);
		}
		update_env(&envp, getcwd(NULL, 0)); //protect getcwd ??
	}
	return (0);
}

int	ft_pwd(char *input)
{
	char *cwd;

	cwd = getcwd(NULL, 0); //automatic allocation of memory needed to copy path /!\ if path is NULL because folder was deleted how to handle the difference
	if (cwd)
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (1);
	}
	free(cwd);
	return (0);
}
