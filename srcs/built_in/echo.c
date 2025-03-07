#include "minishell.h"

static int	is_no_nl(char *str, int *no_nl)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	*no_nl = 1;
	return (1);
}

static int	ft_print_echo(char **cmds, int index, int no_nl, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (cmds[index])
	{
		while (cmds[index][i])
		{
			if (cmds[index][i] == '$' && cmds[index][i + 1] && cmds[index][i + 1] == '?')
			{
				ft_dprintf(STDOUT_FILENO, "%d", minishell->exit_status);
				i++;
			}
			else
				ft_dprintf(STDOUT_FILENO, "%c", cmds[index][i]);
			i++;
		}
		index++;
		if (cmds[index])
			ft_dprintf(STDOUT_FILENO, " ");
	}
	if (!no_nl)
		printf("\n");
	return (0);
}

int	ft_echo(char **cmds, t_minishell *minishell)
{
	int	ret;
	int	no_nl;
	int	i;

	ret = 0;
	i = 0;
	no_nl = 0;
	if (!cmds[++i])
	{
		ft_dprintf(STDOUT_FILENO, "\n");
		return (ret);
	}
	while (cmds[i] && is_no_nl(cmds[i], &no_nl))
		i++;
	if (!cmds[i])
		return (ret);
	ft_print_echo(cmds, i, no_nl, minishell);
	return (ret);
}
