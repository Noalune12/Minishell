#include "minishell.h"

void	remove_export(char **cmds, int i)
{
	int	j;

	if (cmds == NULL || cmds[i] == NULL)
		return ;
	free(cmds[i]);
	j = i;
	while (cmds[j])
	{
		cmds[j] = cmds[j + 1];
		j++;
	}
	cmds[j] = NULL;
}

// void	print_double(char **strs)
// {
// 	int	i;

// 	i = 0;
// 	while (strs[i])
// 	{
// 		printf(BLUE"%s\n"RESET, strs[i]);
// 		i++;
// 	}
// }

void	check_if_space(char **cmds, int *ret)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[++i])
	{
		j = 0;
		while (cmds[i][j] && cmds[i][j] != '=')
		{
			if ((!ft_isalnum(cmds[i][j]) && cmds[i][j] != '_'
				&& cmds[i][j] != '+') || (cmds[i][j] && cmds[i][j] == '+'
				&& ((cmds[i][j + 1] && cmds[i][j + 1] != '=')
				|| !cmds[i][j + 1])))
			{
				ft_dprintf(STDERR_FILENO,
					"bash: export: `%s': not a valid identifier\n", cmds[i]);
				*ret = 1;
				remove_export(cmds, i);
				i--;
				break ;
			}
			j++;
		}
	}
}

int	check_export(char **cmds)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmds[i])
	{
		if (cmds[i][0] != '_' && !ft_isalpha(cmds[i][0]))
		{
			ft_dprintf(STDERR_FILENO,
				"bash: export: `%s': not a valid identifier\n", cmds[i]);
			ret = 1;
			remove_export(cmds, i);
		}
		else
			i++;
	}
	check_if_space(cmds, &ret);
	return (ret);
}
