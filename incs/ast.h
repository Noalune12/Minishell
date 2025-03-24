#ifndef AST_H
# define AST_H

# include <stdbool.h>

typedef struct s_ast			t_ast;
typedef struct s_token			t_token;
typedef enum e_node_type		t_node_type;

typedef struct s_branch
{
	t_token	*token_redir;
	t_ast	*node_cmd;
	t_ast	*node_redir;
	t_ast	*node;
}	t_branch;


void	free_ast(t_ast *node);
void	ft_free(char **split);

int		is_redir_node(t_node_type type);
int		is_redir_node_not_heredoc(t_node_type type);
int		is_operator_node(t_node_type type);
int		still_heredoc_left(t_token *token);

char	**update_heredoc(char **cmds, char *content);

t_ast	*build_ast(t_token **token, bool *exec_status);
t_ast	*create_ast_tree_node(t_node_type type, char *content, bool expand, t_ast *parent);
t_ast	*create_branch(t_token **token, t_ast *root, t_ast *sub_ast);
t_ast	*add_up(t_ast *root, t_ast *node);
t_ast	*add_to_rightmost(t_ast *root, t_ast *node);
t_ast	*add_to_left(t_ast *root, t_ast *node);
t_ast	*add_down_right(t_ast *root, t_ast *node);
t_ast	*add_to_ast(t_ast *root, t_ast *node);
t_ast	*error_handling_ast(t_ast *root, t_ast *sub_ast, char *str);

#endif
