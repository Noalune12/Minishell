/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:16:40 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:16:42 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include <stdbool.h>

# define PRINT_ACTIVATED	"print %s\t%sactivated%s\n"
# define PRINT_UNACTIVATED	"print %s\t%sunactivated%s\n"

# define PTREE				"tree"
# define PTOKENS			"tokens"

typedef struct s_minishell	t_minishell;
typedef void				(*t_option_handler)(t_minishell *);

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

void	ast_wrapper(t_minishell *minishell);
void	options_wrapper(t_minishell *minishell);
void	print_option(t_options_enum option, t_minishell *minishell);
void	print_toggled_options(t_minishell *minishell);
void	print_tokens(t_minishell *minishell);
void	tokens_wrapper(t_minishell *minishell);
void	update_options(bool *to_update);

int		print_options_wrapper(char **cmds, t_minishell *minishell);
int		update_ptokens_wrapper(char **cmds, t_minishell *minishell);
int		update_ptree_wrapper(char **cmds, t_minishell *minishell);

#endif
