#include "minishell.h"

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->envp = env_init(envp);
}
