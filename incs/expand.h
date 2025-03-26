/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:15:17 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:52:50 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include <stdbool.h>

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
	bool		in_dquotes;
	bool		in_squotes;
	char		*expanded;
	char		*str;
	int			*exp;
	int			*quote;
	size_t		i;
	size_t		j;
	t_list		*env;
	t_minishell	*minishell;
}	t_expand_data;

typedef struct s_expanded_str_len
{
	bool	in_dquotes;
	bool	in_squotes;
	char	*exit_code_str;
	char	*var_name;
	size_t	i;
	size_t	total_len;
	size_t	var_len;
}	t_exp_len;

typedef struct s_heredoc_data
{
	char	*expanded;
	char	*str;
	size_t	i;
	size_t	j;
	ssize_t	expanded_len;
	t_list	*env;
}	t_heredoc_data;

typedef struct s_dollar_exp
{
	char	*str;
	char	*expanded;
	size_t	*i_ptr;
	size_t	*j_ptr;
	t_list	*env;
}	t_dollar_exp;

void	copy_var_value(char *var_name, t_expand_data *data);

char	*expand_heredoc(char *str, t_minishell *minishell);
char	*ft_getenv(char *var_name, t_list *env);
char	*expand_env_vars(char *str, t_minishell *minishell, \
														int *exp, int *quote);

ssize_t	get_expanded_str_len(char *s, t_minishell *minishell);

size_t	get_var_len(char *str, size_t i);

int		handle_dollar_quoted(t_expand_data *data, char quote_char);
int		handle_dollar_sign(t_expand_data *data);
int		handle_exit_code(char *expanded, size_t *i, size_t *j, int exit_code);
int		handle_heredoc_dollar_sign(t_heredoc_data *data);
int		process_character(t_expand_data *data);
int		init_heredoc_expand(t_heredoc_data *data, char *str, \
														t_minishell *minishell);

bool	init_expand_data(t_expand_data *data, char *str, \
														t_minishell *minishell);
bool	update_quotes_expand(char c, bool *in_squotes, bool *in_dquotes, \
																	int *quote);

#endif
