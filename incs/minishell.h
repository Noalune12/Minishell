#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#define TRUE 1
#define FALSE 0
#define T_ERR 1
#define T_SEP 2 // < > |
#define T_BUILTIN 3
#define T_CMD 4
#define T_ABS 5
#define T_FILE 6
#define T_WORD 7
#define T_RET 8

# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define RESET   "\033[0m"
# define PURPLE "\033[0;35m"

typedef struct s_args
{
	char	*arg;
	int		token;
	void	*next;
}	t_args;

t_args	*create_struct(t_args *args);
void	add_node(t_args **args);
void	free_struct(t_args *args);

void	parse_quote(const char *input);
bool	parse_input(const char *input, t_args *args);


#endif
