#ifndef MINISHELL_H
# define MINISHELL_H

// typedef struct s_fds			t_fds;
typedef struct s_options		t_options;
typedef struct s_list			t_list;
typedef struct s_ast			t_ast;

extern int	g_signal_received;

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# include "expand.h"
# include "ft_dprintf.h"
# include "libft.h"
# include "options.h"
# include "fd.h" // cannot include it otherwise --> error
# include "types.h"

# define RED		"\001\033[0;31m\002"
# define BOLD_RED	"\001\033[1;31m\002"
# define GREEN		"\001\033[1;32m\002"
# define YELLOW		"\001\033[1;33m\002"
# define BLUE		"\001\033[1;34m\002"
# define WHITE_BOLD	"\001\033[1;37m\002"
# define PURPLE		"\001\033[0;35m\002"
# define CYAN		"\001\033[1;36m\002"
# define RESET		"\001\033[0m\002"

# define GREEN_ARROW "\001\033[32m\xe2\x9e\002\x9c\001\033[0m\002"
# define RED_ARROW   "\001\033[31m\xe2\x9e\002\x9c\001\033[0m\002"


// liste de define derreurs + dautres plus tard
# define FILENAME_SYNTAX "syntax error: missing filename after redirection\n"
# define NEWLINE_SYNTAX "minishell: syntax error near unexpected token `newline'\n"
# define STR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define CHAR_SYNTAX "minishell: syntax error near unexpected token `%c'\n"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define FILE_NOT_FOUND "minishell: %s: %s: No such file or directory\n"
# define HEREDOC_ERROR_MESSAGE "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"
# define ERROR_SYNTAX_TO_MODIFY "syntax error\n" // a modifier
# define ERROR_OUTFILE "minishell: %s: Permission denied\n" // a delete ?
# define ERROR_INFILE "minishell: %s: No such file or directory\n"
# define SIGQUIT_MESSAGE "Quit (core dumped)\n"
# define DOT_ERR "minishell: %s: filename argument required\n"
# define IS_REDIR "minishell: %s: Is a directory\n"

// Error builtin

// liste de define plutot que decrire en brut

# define PWD			"PWD"
# define OLDPWD			"OLDPWD"
# define PATH			"PATH"
# define SHLVL			"SHLVL"
# define HOME			"HOME"
# define USER			"USER"
# define ENV_DEFAULT	"_/usr/bin/env"
// liste de define de message derreur


// heredoc defines

typedef struct	s_token
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
	bool		exec_status;
	int			exit_status;
	int			is_pipe;
	pid_t		pid;
	int			fd_in;
	int			fd_out;
	t_options	*options;
	t_list		*envp;
	t_token		*token;
	t_ast		*ast_node;
	t_fds		fds;
}	t_minishell;




void	minishell_main_loop(t_minishell *minishell);
char	*read_input(t_minishell *minishell);





// void	free_list(t_list *list);
void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);

void	handle_signal_main(void);
void	handle_signal_child(void);

bool	replace_token(t_list *current, t_list *new_tokens);
void	cleanup_shell(t_minishell *minishell);
void	cleanup_loop(t_minishell *minishell);
void	cleanup_exit(t_minishell *minishell);





/**
 * @brief Checks if standard input and output are attached to a TTY.
 *
 * This function verifies that both STDIN and STDOUT are associated with a
 * terminal device.
 * If either is not a TTY (for example, when the shell is executed in a
 * non-interactive context like a pipeline),
 * an error message is printed to STDERR and the program exits successfully.
 *
 * @note The function uses ft_dprintf to output the error message; consider
 * replacing it with your custom
 * stderr printing function if needed.
 */
void	tty_check(void);

/**
 * @brief Updates the PWD environment variable in the environment list.
 *
 * This function retrieves the current working directory using getcwd,
 * constructs a new string in the
 * format "PWD=<current_working_directory>", and updates the environment
 * list accordingly.
 * If the environment list is empty or if any memory allocation fails,
 * no changes are made.
 *
 * @param env Pointer to the environment list.
 */
void	update_pwd(t_list **env);

/**
 * @brief Updates the SHLVL environment variable in the environment list.
 *
 * This function searches for the "SHLVL" node in the environment list,
 * converts its current value,
 * increments it (unless it exceeds 999 or is non-positive, in which case it
 * resets to 1), and updates the node.
 * An error message is printed to STDERR if SHLVL is too high.
 *
 * @param env The environment list.
 */
void	update_shlvl(t_list *env);

/*	----------- parsing ----------------------------------------------------- */


/* ---- ast */

/* ---- exec */

/* test signal */

void	init_global(void);
void	handle_signal_wait(void);

char	*read_input(t_minishell *minishell);

int		return_global(void);


/* ---- REFACTOR T_TOKEN TESTS ---- */

void	free_token_list(t_token *tokens);
bool	add_token(t_token **tokens, char *content, t_node_type type);
bool	add_token_in_place(t_token **tokens, char *content, t_node_type type);

t_token	*init_token_node(char *content, t_node_type type);

void	split_operators(t_minishell *minishell);
void	tokenize_input(t_minishell *minishell);




void	syntax_check(t_minishell *minishell);
int		check_unbalanced_parenthesis(t_token *token, int *paren_count,
									t_minishell *minishell);
int	check_parentheses_tokens(t_token *current, t_token *next,
								t_minishell *minishell);

void	add_manpath_to_env(t_list **env);

int		add_or_replace_env(char *content, t_list **env, int len, int add);

/* ---- HANDLE FD ---- */



t_node_type	get_operator_type(const char *content, \
	size_t i, size_t op_len);

#endif
