// #ifndef MINISHELL_H
// # define MINISHELL_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdbool.h>
// #include <signal.h>
// #include "libft.h"
// #include "get_next_line.h"
// #include "ft_printf.h"

// // typedef struct s_arg	t_arg;

// #define TRUE 1
// #define FALSE 0
// #define T_ERR 1
// #define T_SEP 2 // < > |
// #define T_BUILTIN 3
// #define T_CMD 4
// #define T_ABS 5
// #define T_FILE 6
// #define T_WORD 7
// #define T_RET 8

// # define RED     "\033[1;31m"
// # define GREEN   "\033[1;32m"
// # define YELLOW  "\033[1;33m"
// # define BLUE    "\033[1;34m"
// # define RESET   "\033[0m"
// # define PURPLE "\033[0;35m"


// // // liste de define derreurs

// # define CMD_NOT_FOUND "bash: %s: command not found\n"
// # define FILE_NOT_FOUND "%s: %s: No such file or directory\n"
// # define QUOTES "'\""

// // typedef enum e_token
// // {
// // 	T_PIPE, // |
// // 	T_HEREDOC, // <<
// // 	T_APPEND, // >>
// // 	T_REDIREC, // "><"
// // 	T_CMD,
// // 	T_BUILTIN,
// // 	T_FD,
// // 	T_AND, // &&
// // 	T_OR, // ||
// // }	t_token;

// // CHOIX ENTRE t_token et t_node_type a faire

// // typedef enum e_node_type
// // {
// // 	NODE_COMMAND,
// // 	NODE_PIPE,
// // 	NODE_AND,
// // 	NODE_OR,
// // }	t_node_type;

// // t_parse reellement utile ?

// // typedef struct s_parse
// // {
// // 	int				t_type;
// // 	void			*content;
// // 	struct s_parse	*next;
// // }	t_parse;



// typedef struct s_node
// {
// 	//t_node_type		type;
// 	//t_token			type;
// 	void			*content;
// 	struct s_node	*left;
// 	struct s_node	*right;
// }	t_node;

// typedef struct s_env
// {
// 	char	*input;
// 	t_list	*envp; // liste chainee de l'environnement (getenv que t'as fais)
// 	t_list	*token; // liste chainee des parametres
// 	t_node	*ast_node;
// }	t_env;

// typedef struct s_args
// {
// 	char	*arg;
// 	int		token;
// 	struct s_args	*next;
// }	t_args;



// // void	create_struct(t_args *args);
// // void	add_node(t_args *args);
// // void	free_struct(t_args *args);
// // void	practice(char *input, t_args *args);

// // bool	parse_input(const char *input, t_args *args);





// #endif

#ifndef MINITEST_H
# define MINITEST_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
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

// memo error code 127 -> no path to command
// liste de define derreurs

# define CMD_NOT_FOUND "bash: %s: command not found\n"
# define FILE_NOT_FOUND "%s: %s: No such file or directory\n"
# define QUOTES "'\""

// typedef enum e_token
// {
// 	T_PIPE, // |
// 	T_HEREDOC, // <<
// 	T_APPEND, // >>
// 	T_REDIREC, // "><"
// 	T_CMD,
// 	T_BUILTIN,
// 	T_FD,
// 	T_AND, // &&
// 	T_OR, // ||
// }	t_token;

// CHOIX ENTRE t_token et t_node_type a faire

// typedef enum e_node_type
// {
// 	NODE_COMMAND,
// 	NODE_PIPE,
// 	NODE_AND,
// 	NODE_OR,
// }	t_node_type;

// t_parse reellement utile ?

// typedef struct s_parse
// {
// 	int				t_type;
// 	void			*content;
// 	struct s_parse	*next;
// }	t_parse;

typedef struct s_node
{
	//t_node_type		type;
	//t_token			type;
	void			*content;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_minishell
{
	char	*input;
	t_list	*envp; // liste chainee de l'environnement (gentenv que t'as fais)
	t_list	*token; // liste chainee des parametres
	t_node	*ast_node;
}	t_minishell;



typedef struct s_args
{
	char	*arg; //
	int		token;
	struct s_args	*next;
}	t_args;

t_list	*env_init(char **envp);

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);
void	free_list(t_list *list);

#endif
