#ifndef OPTIONS_H
# define OPTIONS_H

typedef struct s_minishell	t_minishell;

typedef enum e_options
{
	AST,
	TOKENS,
	OPTIONS,
}	t_options_enum;

typedef struct s_options
{
	bool	display_ast;
	bool	display_tokens;
}	t_options;

void	update_options(bool *to_update);
void	check_entry(t_minishell *minishell);

#endif
