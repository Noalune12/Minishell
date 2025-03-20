#include "minishell.h"

char	**update_heredoc(char **cmds, char *content)
{
	char	**new_cmd;

	new_cmd = (char **)malloc(2 * sizeof(char *));
	new_cmd[0] = ft_strdup(content);
	new_cmd[1] = NULL;
	ft_free(cmds);
	return (new_cmd);
}

int	still_heredoc_left(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && (is_operator_node(temp->type) == 0
			&& temp->type != NODE_CLOSE_PAR))
	{
		if (temp->type == NODE_HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}
