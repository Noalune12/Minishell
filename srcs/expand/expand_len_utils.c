#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static inline bool	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

inline size_t	get_var_len(char *str, size_t i)
{
	size_t	var_len;

	var_len = 0;
	while (str[i + var_len] && is_var_char(str[i + var_len]))
		var_len++;
	return (var_len);
}
