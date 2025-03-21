#ifndef EXPAND_H
# define EXPAND_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_minishell	t_minishell;
typedef struct s_list		t_list;

typedef struct s_quotes
{
	char	*result;
	char	*original;
	int		len;
	bool	in_squotes;
	bool	in_dquotes;
}	t_quotes;

typedef struct s_expand_data
{
	t_list		*env;
	t_minishell	*minishell;
	char		*str;
	char		*expanded;
	size_t		i;
	size_t		j;
	int			*exp;
	int			*quote;
	bool		in_squotes;
	bool		in_dquotes;
}	t_expand_data;

typedef struct s_expanded_str_len
{
	size_t	i;
	size_t	total_len;
	size_t	var_len;
	char	*var_name;
	char	*exit_code_str;
	bool	in_squotes;
	bool	in_dquotes;
}	t_exp_len;

char	*ft_getenv(char *var_name, t_list *env);
char	*expand_env_vars(char *str, t_minishell *minishell, int *exp, int *quote);

size_t	get_expanded_str_len(char *str, t_minishell *minishell);
size_t	get_var_len(char *str, size_t i);

void	copy_var_value(char *var_name, char *expanded, size_t *j, t_list *env);

int		handle_dollar_sign(char *str, char *expanded, size_t *i, size_t *j, t_list *env);
int 	handle_exit_code(char *expanded, size_t *i, size_t *j, int exit_code);
int		handle_dollar_quoted(t_expand_data *data, char quote_char);
int		handle_variable_expansion(t_expand_data *data);
int		process_character(t_expand_data *data);

bool	init_expand_data(t_expand_data *data, char *str, t_minishell *minishell);
bool	init_expand_len_data(t_exp_len *data, t_minishell *minishell);
bool	update_quotes_expand(char c, bool *in_squotes, bool *in_dquotes, \
																	int *quote);

#endif
