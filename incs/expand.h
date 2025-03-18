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

bool	handle_quotes_expand(char c, bool *in_squotes, bool *in_dquotes, int *quote);

char	*expand_env_vars(char *str, t_list *env, t_minishell *minishell, int *exp, int *quote);
char	*ft_getenv(char *var_name, t_list *env);

size_t	get_expanded_str_len(char *str, t_list *env, t_minishell *minishell);
size_t	get_var_len(char *str, size_t i);

void	copy_var_value(char *var_name, char *expanded, size_t *j, t_list *env);

#endif
