/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:13 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 11:34:54 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include <stdbool.h>

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;

# define CURRENT_DIR	"."

typedef struct s_wildcard
{
	DIR				*dir;
	struct dirent	*entry;
	char			**file_names;
	int				i;
	int				count;
}	t_wildcard;

void	expand_wildcards(t_minishell *minishell);

bool	add_filename(char **filenames, char *name, int index);
bool	contain_wildcard(char *token);
bool	should_include_file(char *pattern, char *filename);
bool	wildcard_match(const char *pattern, const char *str);

char	**allocate_2d_array(int count);
char	**get_file_names(char *pattern, int count);

int		count_matches(char *pattern);

#endif
