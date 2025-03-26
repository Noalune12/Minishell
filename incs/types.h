/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:07 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 11:33:57 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_ast		t_ast;
typedef struct s_cmd		t_cmd;
typedef struct s_fd_info	t_fd_info;
typedef struct s_fds		t_fds;
typedef struct s_list		t_list;
typedef struct s_minishell	t_minishell;
typedef struct s_options	t_options;
typedef struct s_token		t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_OR,
	NODE_AND,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_HEREDOC,
	NODE_APPEND,
	NODE_OPEN_PAR,
	NODE_CLOSE_PAR,
	NODE_BUILTIN
}	t_node_type;

#endif
