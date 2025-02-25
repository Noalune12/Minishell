#include "minishell.h"

static int	add_or_replace_env(char *content, t_list **env, int len, int add)
{
	t_list	*temp;
	char	*var;
	char	*env_var;

	var = ft_strndup(content, len);
	temp = *env;
	while (temp)
	{
		env_var = ft_strndup(temp->content, ft_strnlen(temp->content, '='));
		if (strcmp(var, env_var) == 0)
		{
			free(env_var);
			break ;
		}
		free(env_var);
		temp = temp->next;
	}
	if (temp && add)
	{
		free(temp->content);
		temp->content = ft_strdup(content);
	}
	else if (!temp)
		add_node(env, content);
	free(var);
	return (0);
}

static char	*remove_plus(char *content)
{
	char	*str;
	int		i;
	int		j;
	bool	plus;

	str = ft_calloc(ft_strlen(content), sizeof(char));
	i = 0;
	j = 0;
	plus = false;
	while (content[i])
	{
		if ((content[i] != '+') || (content[i] == '+' && plus == true))
		{
			str[j] = content[i];
			j++;
		}
		if (content[i] == '+')
			plus = true;
		i++;
	}
	free(content);
	return (str);
}

static int	add_or_append_env(char *content, t_list **env, int len)
{
	t_list	*temp;
	char	*var;
	char	*env_var;
	char	*append;
	char	*temp_str;
	int		equal;

	equal = 0;
	var = ft_strndup(content, len - 2);
	temp = *env;
	while (temp)
	{
		env_var = ft_strndup(temp->content, ft_strnlen(temp->content, '='));
		if (strcmp(var, env_var) == 0)
		{
			free(env_var);
			break ;
		}
		free(env_var);
		temp = temp->next;
	}
	if (temp && ft_strchr(temp->content, '='))
		equal = 1;
	if (temp)
	{
		append = ft_strdup(content + len);
		temp_str = temp->content;
		if (equal == 1)
		{
			temp->content = ft_strjoin(temp->content, append);
			free(temp_str);
			free(append);
		}
		else
		{
			temp->content = ft_strjoin(temp->content, "=");
			free(temp_str);
			temp_str = temp->content;
			temp->content = ft_strjoin(temp->content, append);
			free(temp_str);
			free(append);
		}
	}
	else if (!temp)
	{
		add_node(env, content);
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->content = remove_plus(temp->content);
	}
	free(var);
	return (0);
}

int	add_export_to_env(char *cmds, t_list **env)
{
	int	i;

	i = 0;
	while (cmds[i] && cmds[i] != '=' && cmds[i] != '+')
		i++;
	if (cmds[i] == '=')
		add_or_replace_env(cmds, env, i, 1);
	else if (!cmds[i])
		add_or_replace_env(cmds, env, i, 0);
	else if (cmds[i] == '+' && cmds[i + 1] == '=' && cmds[i + 2])
		add_or_append_env(cmds, env, i + 2);
	return (0);
}
