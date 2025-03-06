#ifndef EXPAND_H
# define EXPAND_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "minishell.h"

// typedef struct s_expand
// {
// 	char	*result;
// 	size_t	i;
// 	size_t	j;
// 	bool	*in_squotes;
// 	bool	*in_dquotes;
// }	t_expand;

// typedef struct s_quotes
// {
// 	char	*result;
// 	size_t	i;
// 	size_t	j;
// 	bool	in_squotes;
// 	bool	in_dquotes;
// }	t_quotes;

bool	handle_quotes_expand(char c, bool *in_squotes, bool *in_dquotes);

char	*expand_env_vars(char *str, t_list *env);
char	*ft_getenv(char *var_name, t_list *env);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*remove_quotes(char *str);

int		ft_isalnum(int c);

size_t	ft_strlen(const char *s);
size_t	get_expanded_str_len(char *str, t_list *env);
size_t	get_result_len(char *str);
size_t	get_var_len(char *str, size_t i);

void	copy_var_value(char *var_name, char *expanded, size_t *j, t_list *env);

#endif
