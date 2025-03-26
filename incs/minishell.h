/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:30 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 11:31:21 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <sys/types.h>

# include "fd.h"
# include "types.h"

extern int	g_signal_received;

typedef struct s_token
{
	char			*content;
	bool			to_expand;
	t_node_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	char		*exec;
	char		*input;
	int			exit_status;
	int			fd_in;
	int			fd_out;
	int			is_pipe;
	bool		exec_status;
	pid_t		pid;
	t_ast		*ast_node;
	t_fds		fds;
	t_list		*envp;
	t_options	*options;
	t_token		*token;
}	t_minishell;

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);
void	minishell_main_loop(t_minishell *minishell);
void	split_operators(t_minishell *minishell);
void	syntax_check(t_minishell *minishell);
void	tokenize_input(t_minishell *minishell);

char	*read_input(t_minishell *minishell);

#endif
