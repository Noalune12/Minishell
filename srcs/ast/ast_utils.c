#include "minishell.h"

t_ast	*create_ast_node(t_node_type type, char *content) // debut de creation de larbre, je vais essayer de faire un affichage de larbre correcte avant de commencer a tout parser correctement
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (content) // vraiment utile de check ca ? techniquement tout est != NULL, dans le doute je laisse pour linstant
		node->content = ft_strdup(content);
	else
		node->content = NULL;
	return (node);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->content)
		free(node->content);
	free(node);
}
