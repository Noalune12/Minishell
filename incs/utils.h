/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:18:57 by lbuisson          #+#    #+#             */
/*   Updated: 2025/07/24 14:17:59 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define IFS_CHARACTERS " \t\n"
# define EXIT_NL		"exit\n"

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef enum e_node_type	t_node_type;

typedef struct s_new_array
{
	char	**new_cmds;
	int		old_len;
	int		new_len;
	int		dest_index;
}	t_new_array;

void	cleanup_exit(t_minishell *minishell);
void	cleanup_loop(t_minishell *minishell);
void	cleanup_shell(t_minishell *minishell);
void	free_token_list(t_token *tokens);

char	**ft_free_double(char **strs);
char	**create_new_cmds_array(char **old_cmds, int old_index, 
								char **file_names, int file_count);

bool	add_token_in_place(t_token **tokens, char *content, t_node_type type);
bool	add_token(t_token **tokens, char *content, t_node_type type);
bool	replace_token(t_list *current, t_list *new_tokens);

#endif
