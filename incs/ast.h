#ifndef AST_H
# define AST_H

# include <stdbool.h>
# include <stdlib.h>

# include "types.h"

typedef struct s_minishell		t_minishell;
typedef struct s_token			t_token;
typedef enum e_node_type		t_node_type;

typedef struct s_cmd
{
	char	*path;
	char	**cmds;
	bool	to_expand;
}	t_cmd;

typedef struct s_ast
{
	t_node_type		type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*root; // top priority node
}	t_ast;

typedef struct s_branch
{
	t_token	*token_redir;
	t_ast	*node_cmd;
	t_ast	*node_redir;
	t_ast	*node;
}	t_branch;

void	build_ast(t_minishell *ms);
void	free_ast(t_ast *node);
void	free_ast_2(t_minishell *minishell);
void	free_tab(char **tab, int i);
void	print_ast(t_minishell *ms, t_ast *node, int depth);
void	print_cmd_node(t_ast *node, char *prefix);
void	print_redirect_node(t_ast *node, char *symbol);

char	**update_heredoc(char **cmds, char *content);

int		is_redir_node(t_node_type type);
int		is_redir_node_not_heredoc(t_node_type type);
int		is_operator_node(t_node_type type);
int		still_heredoc_left(t_token *token);

t_ast	*create_ast_tree_node(t_node_type type, char *content,
			bool expand, t_ast *parent);
t_ast	*create_branch(t_token **token, t_ast *root, t_ast *sub_ast);
t_ast	*add_up(t_ast *root, t_ast *node);
t_ast	*add_to_rightmost(t_ast *root, t_ast *node);
t_ast	*add_to_left(t_ast *root, t_ast *node);
t_ast	*add_to_right_top_or_insert(t_ast *root, t_ast *node);
t_ast	*add_to_ast(t_ast *root, t_ast *node);
t_ast	*error_handling_ast(t_ast *root, t_ast *sub_ast);

#endif
