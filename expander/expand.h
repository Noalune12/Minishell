#ifndef EXPAND_H
# define EXPAND_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

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

char	*expand_env_vars(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*remove_quotes(char *str);

size_t	get_expanded_str_len(char *str);
size_t	ft_strlen(const char *s);
size_t	get_var_len(char *str, size_t i);
size_t	get_result_len(char *str);

int		ft_isalnum(int c);

bool	handle_quotes(char c, bool *in_squotes, bool *in_dquotes);

void	copy_var_value(char *var_name, char *expanded, size_t *j);

#endif
