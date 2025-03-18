#include "minishell.h"

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

static int	error_handling(char *str)
{
	if (str)
		free(str);
	ft_dprintf(STDERR_FILENO, "Malloc failed\n");
	return (1);
}

static int	create_var_export(t_list **env, char *content)
{
	char	*temp_content;

	temp_content = remove_plus(content);
	if (!temp_content)
		return (1);
	if (!add_node(env, temp_content))
		return (error_handling(temp_content));
	free(temp_content);
	return (0);
}

static int	append_export(char *content, int len, int equal, t_list *temp)
{
	char	*append;
	char	*temp_str;

	append = ft_strdup(content + len);
	if (!append)
		return (error_handling(NULL));
	if (equal == 0)
	{
		temp_str = ft_strjoin(temp->content, "=");
		if (!temp_str)
			return (error_handling(append));
		swap_strs(&temp->content, &temp_str);
	}
	temp_str = ft_strjoin(temp->content, append);
	if (!temp_str)
		return (error_handling(append));
	swap_strs(&temp->content, &temp_str);
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
	if (find_env_var_node(var, &temp) == 1) // ?? elle return jamais 1 ta fonction Lou-Anne ? Tu fais quoi
		return (1);
	if (temp && ft_strchr(temp->content, '='))
		equal = 1;
	if (temp)
		return (append_export(content, len, equal, temp));
	else if (!temp)
		return (create_var_export(env, content));
	return (0);
}
