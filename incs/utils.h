#ifndef UTILS_H
# define UTILS_H

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef enum e_node_type	t_node_type;

char	**ft_free_double(char **strs);

void	cleanup_exit(t_minishell *minishell);
void	cleanup_loop(t_minishell *minishell);
void	cleanup_shell(t_minishell *minishell);
void	free_token_list(t_token *tokens);

bool	add_token_in_place(t_token **tokens, char *content, t_node_type type);
bool	add_token(t_token **tokens, char *content, t_node_type type);
bool	replace_token(t_list *current, t_list *new_tokens);


#endif
