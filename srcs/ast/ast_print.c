#include "minishell.h"

// static void	_print_tree(t_ast *root, size_t space);
// static void	format(t_ast *root);

// void	print_tree(t_ast *root)
// {
// 	ft_printf("<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->\n");
// 	_print_tree(root, 0);
// 	ft_printf("\n\n<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->\n");
// }

// static void	_print_tree(t_ast *root, size_t space)
// {
// 	size_t	i;
// 	i = 6;
// 	if (root == NULL)
// 		return ;
// 	space += 6;
// 	_print_tree(root->right, space);
// 	ft_printf("\n");
// 	while (space > i++)
// 		ft_printf(" ");
// 	format(root);
// 	_print_tree(root->left, space);
// }

// static void	format(t_ast *root)
// {
// 	size_t	i;

// 	if (root->type == NODE_COMMAND)
// 	{
// 		i = 0;
// 		while ((root->content) != NULL)
// 		{
// 			ft_printf("%s ", root->content);
// 			i++;
// 		}
// 	}
// 	else if (root->type == NODE_REDIRECTR)
// 		ft_printf("<:%s", root->content);
// 	else if (root->type == NODE_REDIRECTL)
// 		ft_printf(">:%s", root->content);
// 	else if (root->type == NODE_HERE_DOC)
// 		ft_printf("<<:%s", root->content);
// 	else if (root->type == NODE_DREDIRECTL)
// 		ft_printf(">>:%s", root->content);
// 	else if (root->type == NODE_AND)
// 		ft_printf("&&");
// 	else if (root->type == NODE_OR)
// 		ft_printf("||");
// 	else if (root->type == NODE_PIPE)
// 		ft_printf("|");
// }


void print_ast(t_ast *node, int depth) {
    if (!node)
        return;

    // On commence par le sous-arbre droit
    if (node->right)
        print_ast(node->right, depth + 3);

    // Affichage du nœud actuel
    for (int i = 0; i < depth; i++)
        printf(" ");

    switch (node->type) {
        case NODE_COMMAND:
            printf("%s\n", node->content ? node->content : "null");
            break;
        case NODE_PIPE:
            printf("|\n");
            break;
        case NODE_REDIR_OUT:
            printf(">:%s\n", node->content ? node->content : "null");
            break;
        case NODE_REDIR_IN:
            printf("<:%s\n", node->content ? node->content : "null");
            break;
        case NODE_AND:
            printf("&&\n");
            break;
        case NODE_OR:
            printf("||\n");
            break;
        case NODE_APPEND:
            printf(">>:%s\n", node->content ? node->content : "null");
            break;
        case NODE_HEREDOC:
            printf("<<:%s\n", node->content ? node->content : "null");
            break;
    }

    // Puis le sous-arbre gauche
    if (node->left)
        print_ast(node->left, depth + 3);
}

// Fonction de test mise à jour
t_ast *create_test_tree(void) {
    // Exemple : echo bonjour > a > b && cat a && cat b
    t_ast *root = create_ast_node(NODE_AND, NULL);
    t_ast *and2 = create_ast_node(NODE_AND, NULL);

    // Commandes cat
    t_ast *cat1 = create_ast_node(NODE_COMMAND, "cat b");
    t_ast *cat2 = create_ast_node(NODE_COMMAND, "cat a");

    // Redirections
    t_ast *redir1 = create_ast_node(NODE_REDIR_OUT, "a");
    t_ast *redir2 = create_ast_node(NODE_REDIR_OUT, "b");
    t_ast *echo = create_ast_node(NODE_COMMAND, "echo bonjour");

    // Construction de l'arbre
    root->right = cat1;
    root->left = and2;

    and2->right = cat2;
    and2->left = redir1;

    redir1->left = redir2;
    redir2->left = echo;

    return root;
}
