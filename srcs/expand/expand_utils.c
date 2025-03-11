#include "expand.h"
#include "minishell.h"

char	*ft_getenv(char *var_name, t_list *env)
{
	char	*var;
	t_list	*temp;
	int		len;

	var = ft_strjoin(var_name, "=");
	if (!var)
		return (NULL);
	temp = env;
	len = ft_strlen(var);
	while (temp)
	{
		if (ft_strncmp(temp->content, var, len) == 0)
		{
			free(var);
			return (temp->content + len);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}

void	copy_var_value(char *var_name, char *expanded, size_t *j, t_list *env)
{
	char	*var_value;

	var_value = ft_getenv(var_name, env);
	if (var_value)
	{
		while (*var_value)
		{
			expanded[*j] = *var_value;
			(*j)++;
			var_value++;
		}
	}
}
