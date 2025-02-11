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
// liste de define derreurs + dautres plus tard

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

// CHOIX ENTRE t_token et t_node_type a faire ----> je pars plus sur t_node_type pas encore sur de moi

typedef enum e_node_type
{
	NODE_ROOT,		// noeud racine, le plus haut de l'arbre
	NODE_COMMAND,	// commande simple
	NODE_ARGUMENT,	// argument de commande
	NODE_PIPE,		// |
	NODE_REDIRECT,	// >, <, >>,
	NODE_HEREDOC	// utile ? ou bien on le met dans redirect au dessus ?
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type; // type noeud definis par lenum
	char			*content; // ce qu'on recupere du parsing
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast; // pas sur du nom, a discuté (t_node, t_ast_node, t_node_ast...)

typedef struct s_minishell
{
	char	*input;
	t_list	*envp; // liste chainee de l'environnement
	t_list	*token; // liste chainee des parametres
	t_ast	*ast_node; // Abstract Syntax Tree
}	t_minishell;

t_list	*env_init(char **envp);
t_list	*find_env_node(t_list *env, const char *var_searched);

void	add_node(t_list **env, char *content); // ????????
void	add_node_test(t_list *args); // ??????? oui je sais
void	free_list(t_list *list);
void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);
void	tty_check(void);
void	update_pwd(t_list **env);
void	update_shlvl(t_list *env);

int		nested_shell(t_list *env_list);

#endif
