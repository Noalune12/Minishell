#include "built_in.h"
#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"

static int	error_handling(char *str, char *message)
{
	if (str)
		free(str);
	ft_dprintf(STDERR_FILENO, "%s", message);
	return (1);
}

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
		return (error_handling(path, "chdir failed"));
	if (update_cd_env(&envp, path, 1) == 1)
		return (error_handling(NULL, "Malloc failed"));
	return (0);
}

static int	ft_cd_path(char **cmds, t_list **envp)
{
	char	*cwd;

	if (ft_strcmp(cmds[1], "-") == 0)
	{
		if (chdir(ft_getenv("OLDPWD", *envp))) //TODO protect ft_getenv ??
		{
			ft_dprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}
	else if (chdir(cmds[1]) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s: ", "cd", cmds[1]);
		perror("");
		return (1);
	}
	cwd = getcwd(NULL, 4096);
	if (!cwd)
	{
		error_handling(NULL, "cd: error retrieving current directory: getcwd: cannot access parent directories: ");
		perror("");
		return (1);
	}
	if (update_cd_env(envp, cwd, 0) == 1)
		return (error_handling(NULL, "Malloc failed"));
	return (0);
}

int	ft_cd(char **cmds, t_minishell *minishell)
{
	if (!cmds[1])
	{
		if (ft_cd_home(minishell->envp) == 1)
			return (1);
	}
	else if (cmds[2])
	{
		ft_dprintf(STDERR_FILENO, TOO_MANY_ARGS, "cd");
		return (1);
	}
	else
	{
		if (ft_cd_path(cmds, &minishell->envp) == 1)
			return (1);
	}
	return (0);
}
