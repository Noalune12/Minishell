#include "built_in.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"

static void	free_env_export(t_list *env)
{
	t_list	*temp;

	if (env == NULL)
		return ;
	temp = env;
	while (temp)
	{
		temp = env->next;
		if (env->content)
			free(env->content);
		free(env);
		env = temp;
	}
}

static int	ft_print_export(t_list *env)
{
	t_list	*sorted;
	t_list	*temp;

	sorted = copy_env(env);
	if (sorted == NULL)
		return (1);
	ft_list_sort(&sorted, &ascii_cmp);
	temp = sorted;
	while (temp)
	{
		ft_dprintf(STDIN_FILENO, "export %s\n", temp->content);
		temp = temp->next;
	}
	free_env_export(sorted);
	return (0);
}

int	ft_export(char **cmds, t_minishell *minishell)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (cmds[++i] == NULL)
	{
		ret = ft_print_export(minishell->envp);
		return (ret);
	}
	else
		ret = check_export(cmds);
	while (cmds[i])
	{
		if (add_export_to_env(cmds[i], &minishell->envp) == 1)
			ret = 1;
		i++;
	}
	return (ret);
}
