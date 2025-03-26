/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:13:40 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 11:22:16 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define BLUE		"\001\033[1;34m\002"
# define BOLD_RED	"\001\033[1;31m\002"
# define CYAN		"\001\033[1;36m\002"
# define GREEN		"\001\033[1;32m\002"
# define PURPLE		"\001\033[0;35m\002"
# define RED		"\001\033[0;31m\002"
# define WHITE_BOLD	"\001\033[1;37m\002"
# define YELLOW		"\001\033[1;33m\002"

# define RESET      "\001\033[0m\002"

# define GREEN_ARROW "\001\033[32m\xe2\x9e\002\x9c\001\033[0m\002"
# define RED_ARROW   "\001\033[31m\xe2\x9e\002\x9c\001\033[0m\002"

# define CHAR_SYNTAX "minishell: syntax error near unexpected token `%c'\n"
# define STR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define NEWLINE_SYNTAX \
					"minishell: syntax error near unexpected token `newline'\n"

# define ENV_DEFAULT    "_/usr/bin/env"
# define MANPATH        "MANPATH=/usr/share/man:"
# define PWD            "PWD"
# define SHLVL          "SHLVL"
# define INIT_SHLVL		"SHLVL=1"
# define RESEARCHPWD	"PWD="
# define RESEARCHSHLVL	"SHLVL="

# define DEFAULT_PROMPT	"minishell$>"

# define MEM_ALLOC_ERR	"Memory allocation error\n"
# define NOT_A_TTY		"minishell: not a tty\n"

#endif
