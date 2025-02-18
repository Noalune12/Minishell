#include "minishell.h"

t_cmd	*add_cmd(char *content)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->path = NULL;
	new_cmd->cmds = (char **)malloc(2 * sizeof(char *));
	new_cmd->cmds[0] = ft_strdup(content);
	new_cmd->cmds[1] = NULL;
	return (new_cmd);
}

t_ast *create_ast_tree_node(t_node_type type, char *content)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = add_cmd(content);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void add_child(t_ast *parent, t_ast *child)
{
	if (!parent->left)
		parent->left = child;
	else
		parent->right = child;
}

char	**update_cmd(char **cmds, char *content)
{
	char	**new_cmds;
	size_t	i;

	i = 0;
	while (cmds[i])
		i++;
	new_cmds = (char **)malloc((i+ 2) * sizeof(char *)); //protect
	i = 0;
	while (cmds[i])
	{
		new_cmds[i] = ft_strdup(cmds[i]);
		i++;
	}
	new_cmds[i] = ft_strdup(content);
	new_cmds[i + 1] = NULL;
	ft_free(cmds);
	return(new_cmds);
}

void ft_swap(t_ast *a, t_ast *b)
{
	t_ast	temp;

	temp = *a;
	*a = *b;
	*b = temp;
	b->left = NULL;
	a->left = b;
}

void create_ast(t_minishell *minishell)
{
	t_list *temp = minishell->token;
	t_ast *command_node = NULL;
	t_ast *prev_cmd = NULL;
	t_ast *current = NULL;
	t_ast *head = NULL;

	while (temp)
	{
		if (ft_strncmp(temp->content, "|\0", ft_strlen(temp->content)) == 0)
		{
			current = create_ast_tree_node(NODE_PIPE, temp->content);
			if (head)
				add_child(current, head);
			head = current;
			prev_cmd = NULL;
		}
		else if (ft_strncmp(temp->content, ">\0", ft_strlen(temp->content)) == 0
		|| ft_strncmp(temp->content, "<\0", ft_strlen(temp->content)) == 0
		|| ft_strncmp(temp->content, ">>\0", ft_strlen(temp->content)) == 0)
		{
			if (ft_strncmp(temp->content, ">\0", ft_strlen(temp->content)) == 0)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_REDIR_OUT, temp->content);
			}
			else if (ft_strncmp(temp->content, "<\0", ft_strlen(temp->content)) == 0)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_REDIR_IN, temp->content);
			}
			else
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_APPEND, temp->content);
			}
			if (head && prev_cmd)
			{
				add_child(prev_cmd, current);
				ft_swap(prev_cmd, current);
				prev_cmd = prev_cmd->left;
			}
			else if (!head)
				head = current;
			else if (!prev_cmd)
				add_child(head, current);
		}
		else
		{
			if (!prev_cmd)
			{
				if (ft_strncmp(temp->content, "echo\0", ft_strlen(temp->content)) == 0
				|| ft_strncmp(temp->content, "cd\0", ft_strlen(temp->content)) == 0
				|| ft_strncmp(temp->content, "pwd\0", ft_strlen(temp->content)) == 0
				|| ft_strncmp(temp->content, "export\0", ft_strlen(temp->content)) == 0
				|| ft_strncmp(temp->content, "unset\0", ft_strlen(temp->content)) == 0
				|| ft_strncmp(temp->content, "env\0", ft_strlen(temp->content)) == 0
				|| ft_strncmp(temp->content, "exit\0", ft_strlen(temp->content)) == 0)
					command_node = create_ast_tree_node(NODE_BUILTIN, temp->content);
				else
					command_node = create_ast_tree_node(NODE_COMMAND, temp->content);
				if (!head)
					head = command_node;
				else
					add_child(current, command_node);
				prev_cmd = command_node;
			}
			else
				prev_cmd->cmd->cmds = update_cmd(prev_cmd->cmd->cmds, temp->content);
		}
		temp = temp->next;
	}
	minishell->ast_node = head;
}
