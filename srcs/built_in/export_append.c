#include "minishell.h"
// malloc not checked

static char	*remove_plus(char *content)
{
	char	*str;
	size_t	i;
	size_t	j;
	bool	plus;

	str = ft_calloc(ft_strlen(content), sizeof(char));
	if (!str)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		return (NULL);
	}
	i = -1;
	j = -1;
	plus = false;
	while (content[++i])
	{
		if ((content[i] != '+') || (content[i] == '+' && plus == true))
			str[++j] = content[i];
		if (content[i] == '+')
			plus = true;
	}
	return (str);
}

static int	create_var_export(t_list **env, char *content)
{
	t_list	*temp;
	char	*temp_content;

	if (!add_node(env, content))
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		return (1);
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp_content = temp->content;
	temp->content = remove_plus(temp->content);
	if (!temp->content)
	{
		free(temp_content); //remove node ??????
		return (1);
	}
	free(temp_content);
	return (0);
}

static int	error_handling(char *str)
{
	if (str)
		free(str);
	ft_dprintf(STDERR_FILENO, "Malloc failed\n");
	return (1);
}

static int	append_exprt(char *content, int len, int equal, t_list *temp)
{
	char	*append;
	char	*temp_str;

	append = ft_strdup(content + len);
	if (!append)
		return (error_handling(NULL));
	temp_str = temp->content;
	if (equal == 0)
	{
		temp->content = ft_strjoin(temp->content, "=");
		if (!temp->content)
			return (error_handling(append));
		free(temp_str);
		temp_str = temp->content;
	}
	temp->content = ft_strjoin(temp->content, append);
	if (!temp->content)
		return (error_handling(append));
	free(temp_str);
	free(append);
	return (0);
}

int	add_or_append_env(char *content, t_list **env, int len)
{
	t_list	*temp;
	char	*var;
	int		equal;

	temp = *env;
	equal = 0;
	var = ft_strndup(content, len - 2);
	if (!var)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		return (1);
	}
	if (find_env_var_node(var, &temp) == 1)
		return (1);
	if (temp && ft_strchr(temp->content, '='))
		equal = 1;
	if (temp)
		return (append_exprt(content, len, equal, temp));
	else if (!temp)
		return (create_var_export(env, content));
	return (0);
}
