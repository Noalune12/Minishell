#include "minishell.h"
#include "limits.h"

int	check_arg_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ') // TODO is whitespace
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		if (str[i] == ' ')
			break ;
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	return (1);
}

static void	skip_whitespace_sign(char *str, int *sign, int *i)
{
	while (str[*i] == ' ') // TODO is whitespace
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	exit_return(char *str)
{
	int					sign;
	int					i;
	unsigned long long	nb;

	sign = 1;
	i = 0;
	nb = 0;
	skip_whitespace_sign(str, &sign, &i);
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (sign == -1 && (sign * (((long long)nb * 10) + (str[i] - 48))
				== LLONG_MIN) && (!str[i + 1] || !isdigit(str[i + 1])))
			return (0);
		if ((long long)nb > (LLONG_MAX - (str[i] - 48)) / 10)
		{
			ft_dprintf(STDOUT_FILENO, EXIT_ERROR, str);
			return (2);
		}
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (sign == 1)
		return (nb % 256);
	return (256 - nb % 256);
}

int	ft_exit(char **cmds, t_minishell *minishell)
{
	int	ret;

	ret = 0;
	if (!cmds[1])
	{
		ft_dprintf(STDOUT_FILENO, "exit\n");
		ret = 0;
	}
	else if (check_arg_exit(cmds[1]) == 0)
	{
		ft_dprintf(STDOUT_FILENO, EXIT_ERROR, cmds[1]);
		ret = 2;
	}
	else if (cmds[2])
	{
		ft_dprintf(STDOUT_FILENO, EXIT_TOO_MANY_ARGS);
		return (1);
	}
	else
		ret = exit_return(cmds[1]);
	free(minishell->input);
	free_ast(minishell->ast_node);
	free_list(minishell->token);
	free_env(minishell);
	exit(ret);
}
