#include "built_in.h"
#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"

static char	*remove_plus(char *content)
{
	char	*str;
	size_t	i;
	size_t	j;
	bool	plus;

	str = ft_calloc(ft_strlen(content), sizeof(char));
	if (str == NULL)
		return (NULL);
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
	char	*temp_content;

	temp_content = remove_plus(content);
	if (temp_content == NULL)
		return (1);
	if (add_node(env, temp_content) == NULL)
	{
		free(temp_content);
		return (1);
	}
	free(temp_content);
	return (0);
}

static int	append_export(char *content, int len, int equal, t_list *temp)
{
	char	*append;
	char	*temp_str;

	append = ft_strdup(content + len);
	if (append == NULL)
		return (1);
	if (equal == 0)
	{
		temp_str = ft_strjoin(temp->content, "=");
		if (temp_str == NULL)
		{
			free(append);
			return (1);
		}
		swap_strs(&temp->content, &temp_str);
	}
	temp_str = ft_strjoin(temp->content, append);
	if (temp_str == NULL)
	{
		free(append);
		return (1);
	}
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
	if (var == NULL)
		return (1);
	if (find_env_var_node(var, &temp) == 1)
		return (1);
	if (temp && ft_strchr(temp->content, '='))
		equal = 1;
	if (temp)
		return (append_export(content, len, equal, temp));
	else if (temp == NULL)
		return (create_var_export(env, content));
	return (0);
}
