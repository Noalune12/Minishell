#include "ast.h"
#include "libft.h"
#include "minishell.h"

static void	print_cmd_value(char *cmd)
{
	if (cmd)
		ft_dprintf(STDERR_FILENO, "%s +", cmd);
	else
		ft_dprintf(STDERR_FILENO, "null +");
}

void	print_cmd_node(t_ast *node, char *prefix)
{
	int	i;

	i = -1;
	printf("%s: ", prefix);
	while (node->cmd->cmds[++i])
		print_cmd_value(node->cmd->cmds[i]);
	printf("\n");
}

static void	print_redirect_value(char *symbol, char *cmd)
{
	if (cmd)
		ft_dprintf(STDERR_FILENO, "%s:%s ", symbol, cmd);
	else
		ft_dprintf(STDERR_FILENO, "%s:null ", symbol);
}

static void	print_single_redirect(char *symbol, char *cmd)
{
	if (cmd)
		printf("%s:%s\n", symbol, cmd);
	else
		printf("%s:null\n", symbol);
}

void	print_redirect_node(t_ast *node, char *symbol)
{
	int	i;

	if (node->type == NODE_REDIR_OUT)
	{
		i = -1;
		while (node->cmd->cmds[++i])
			print_redirect_value(symbol, node->cmd->cmds[i]);
		printf("\n");
	}
	else
		print_single_redirect(symbol, node->cmd->cmds[0]);
}
