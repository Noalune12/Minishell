#include "built_in.h"
#include "env.h"
#include "libft.h"

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

static int	update_cd_oldpwd(t_list **envp, t_list *env_oldpwd, t_list *env_pwd)
{
	char	*temp;

	if (env_oldpwd && env_pwd)
	{
		temp = ft_strjoin(OLDPWD_EQUAL, env_pwd->content + 4);
		if (temp == NULL)
			return (1);
		swap_strs(&env_oldpwd->content, &temp);
	}
	else if (env_oldpwd == NULL && env_pwd)
	{
		temp = ft_strjoin(OLDPWD_EQUAL, env_pwd->content + 4);
		if (temp == NULL)
			return (1);
		if (add_node(envp, temp) == NULL)
		{
			free(temp);
			return (1);
		}
		free(temp);
	}
	else if (remove_node(envp, OLDPWD) == 1)
		return (1);
	return (0);
}

static int	update_cd_pwd(t_list **envp, t_list *env_pwd, char *path)
{
	char	*temp;

	temp = ft_strjoin(PWD_EQUAL, path);
	if (temp == NULL)
		return (1);
	if (env_pwd)
		swap_strs(&env_pwd->content, &temp);
	else
	{
		if (add_node(envp, temp) == NULL)
		{
			free(temp);
			return (1);
		}
		free(temp);
	}
	return (0);
}

int	update_cd_env(t_list **envp, char *path, int to_home)
{
	t_list	*env_oldpwd;
	t_list	*env_pwd;

	env_oldpwd = find_info_env(envp, OLDPWD_EQUAL, 1);
	if (env_oldpwd == NULL)
		env_oldpwd = find_info_env(envp, OLDPWD_EQUAL, 0);
	env_pwd = find_info_env(envp, PWD_EQUAL, 1);
	if (env_pwd == NULL)
		env_pwd = find_info_env(envp, PWD, 0);
	if (update_cd_oldpwd(envp, env_oldpwd, env_pwd) == 1)
	{
		if (to_home == 0)
			free(path);
		return (1);
	}
	if (update_cd_pwd(envp, env_pwd, path) == 1)
	{
		if (to_home == 0)
			free(path);
		return (1);
	}
	if (to_home == 0)
		free(path);
	return (0);
}
