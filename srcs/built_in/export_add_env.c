#include "built_in.h"
#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"

int	find_env_var_node(char *var, t_list **env) // credit a Sammy pour avoir trouvé ca
{
	char	*env_var;
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		env_var = ft_strndup(temp->content, ft_strnlen(temp->content, '='));
		if (!env_var)
		{
			free(var);
			ft_dprintf(STDERR_FILENO, "Malloc failed\n");
			return (1); // j'ai remplacé par 1 parce que
		}
		if (ft_strcmp(var, env_var) == 0)
		{
			free(env_var);
			break ;
		}
		free(env_var);
		temp = temp->next;
	}
	*env = temp;
	free(var);
	return (0);
}

static int	add_or_replace_condition(char *content, t_list **env,
	int add, t_list *temp)
{
	char	*temp_content;

	if (temp && add)
	{
		temp_content = temp->content;
		temp->content = ft_strdup(content);
		if (!temp->content)
		{
			temp->content = temp_content;
			ft_dprintf(STDERR_FILENO, "Malloc failed\n");
			return (1);
		}
		free(temp_content);
	}
	else if (!temp)
	{
		if (!add_node(env, content))
		{
			ft_dprintf(STDERR_FILENO, "Malloc failed\n");
			return (1);
		}
	}
	return (0);
}

int	add_or_replace_env(char *content, t_list **env, int len, int add)
{
	t_list	*temp;
	char	*var;

	var = ft_strndup(content, len);
	temp = *env;
	if (!var)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		return (1);
	}
	if (find_env_var_node(var, &temp) == 1)
		return (1);
	if (add_or_replace_condition(content, env, add, temp) == 1)
		return (1);
	return (0);
}

int	add_export_to_env(char *cmds, t_list **env)
{
	int	i;

	i = 0;
	while (cmds[i] && cmds[i] != '=' && cmds[i] != '+')
		i++;
	if (cmds[i] == '=')
	{
		if (add_or_replace_env(cmds, env, i, 1) == 1)
			return (1);
	}
	else if (!cmds[i])
	{
		if (add_or_replace_env(cmds, env, i, 0) == 1)
			return (1);
	}
	else if (cmds[i] == '+' && cmds[i + 1] == '=')
	{
		if (add_or_append_env(cmds, env, i + 2) == 1)
			return (1);
	}
	return (0);
}
