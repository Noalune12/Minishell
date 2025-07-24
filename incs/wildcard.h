/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:13 by lbuisson          #+#    #+#             */
/*   Updated: 2025/07/24 15:49:27 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include <stdbool.h>

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_exp_qu		t_exp_qu;

# define CURRENT_DIR	"."

typedef struct s_wildcard
{
	DIR				*dir;
	struct dirent	*entry;
	char			**file_names;
	int				i;
	int				count;
}	t_wildcard;

bool	add_filename(char **filenames, char *name, int index);
bool	contain_wildcard(char *token);
bool	is_ambiguous_redirect(char *original_pattern);
bool	should_include_file(char *pattern, char *filename);
bool	wildcard_match(const char *pattern, const char *str);
bool	handle_wildcard_expansion(t_ast *node, t_exp_qu *exp_qu);

char	**allocate_2d_array(int count);
char	**get_file_names(char *pattern, int count);
char	**expand_wildcard_in_cmds(char **cmds, int index);

int		count_matches(char *pattern);
int		count_wildcard_matches(char *pattern);
int		qu_check(t_ast *node, t_exp_qu *exp_qu);
int		check_redirect_ambiguity(t_ast *node, t_exp_qu *exp_qu, \
					char *original_pattern);
int	init_expansion_data(t_ast *node, t_exp_qu *exp_qu, \
				t_minishell *minishell, char **original_pattern);

void	expand_condition(t_ast *node, t_exp_qu *exp_qu);


#endif
