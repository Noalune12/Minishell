#ifndef WILDCARD_H
# define WILDCARD_H

# include <stdbool.h>

typedef struct s_token	t_token;

t_token	*expand_wildcards(t_token *tokens, bool *exec_status);

void	cleanup_file_names(char **file_names, int count);
void	free_file_names_array(char **file_names);

bool	contain_wildcard(char *token);
bool	should_include_file(char *pattern, char *filename);
bool	wildcard_match(const char *pattern, const char *str);

char	**allocate_2d_array(int count);
char	**get_file_names(char *pattern, int count);

int		count_matches(char *pattern);

#endif
