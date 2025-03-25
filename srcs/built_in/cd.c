#include "built_in.h"
#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"

char	*find_home(t_list *env)
{
	t_list	*temp;
	char	*home;

	temp = env;
	home = NULL;
	if (temp->content == NULL)
		return (NULL);
	while (temp)
	{
		if (ft_strncmp(temp->content, HOME_EQUAL, 5) == 0)
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
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, CD_HOME);
		return (1);
	}
	if (chdir(path) != 0)
	{
		free(path);
		return (1);
	}
	if (update_cd_env(&envp, path, 1) == 1)
		return (1);
	return (0);
}

static int	make_chdir(char **cmds, t_list **envp)
{
	char	*get_env;

	get_env = ft_getenv(OLDPWD, *envp);
	if (get_env == NULL)
		return (1);
	if (ft_strcmp(cmds[1], "-") == 0)
	{
		if (chdir(get_env) != 0)
		{
			ft_dprintf(STDERR_FILENO, OLDPWD_NOT_SET);
			return (1);
		}
	}
	else if (chdir(cmds[1]) != 0)
	{
		ft_dprintf(STDERR_FILENO, DOUBLE_STR_ERR, CD, cmds[1]);
		perror("");
		return (1);
	}
	return (0);
}

static int	ft_cd_path(char **cmds, t_list **envp)
{
	char	*cwd;

	if (make_chdir(cmds, envp) == 1)
		return (1);
	cwd = getcwd(NULL, 4096);
	if (cwd == NULL)
	{
		ft_dprintf(STDERR_FILENO, CWD_ERROR, CD);
		perror("");
		return (1);
	}
	if (update_cd_env(envp, cwd, 0) == 1)
		return (1);
	return (0);
}

int	ft_cd(char **cmds, t_minishell *minishell)
{
	if (cmds[1] == NULL)
	{
		if (ft_cd_home(minishell->envp) == 1)
			return (1);
	}
	else if (cmds[2])
	{
		ft_dprintf(STDERR_FILENO, TOO_MANY_ARGS, CD);
		return (1);
	}
	else
	{
		if (ft_cd_path(cmds, &minishell->envp) == 1)
			return (1);
	}
	return (0);
}
