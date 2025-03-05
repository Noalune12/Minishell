#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_list			t_list;
typedef struct s_ast			t_ast;

# include <unistd.h>
# include "../expander/expand.h"

// int	g_signal_received;

// void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);
// void	free_env(t_minishell *minishell);
// void	tty_check(void);

// #endif

// #ifndef MINISHELL_H
// # define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_dprintf.h"
# include <sys/wait.h>
# include <fcntl.h>


# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define RESET		"\033[0m"
# define PURPLE		"\033[0;35m"

// memo error code 127 -> no path to command
// liste de define derreurs + dautres plus tard
# define FILENAME_SYNTAX "syntax error: missing filename after redirection\n"
# define NEWLINE_SYNTAX "syntax error near unexpected token `newline'\n"
# define STRING_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define CHAR_SYNTAX "minishell: syntax error near unexpected token `%c'\n"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define FILE_NOT_FOUND "minishell: %s: %s: No such file or directory\n"
# define FIRST_HEREDOC_ERROR_MESSAGE "warning: here-document delimited by end-of-file (wanted `%s')\n"
# define ERROR_SYNTAX_TO_MODIFY "syntax error\n" // a modifier
# define ERROR_OUTFILE "minishell: %s: Permission denied\n"
# define ERROR_INFILE "minishell: %s: No such file or directory\n"

// Error builtin
# define EXIT_ERROR "minishell: exit: %s: numeric argument required\n"
# define TOO_MANY_ARGS "minishell: %s: too many arguments\n"
# define EXPORT_ERROR "minishell: export: `%s': not a valid identifier\n"
# define CD_HOME "minishell: cd: HOME not set\n"
# define PWD_ERROR "minishell: pwd: %s: invalid option\npwd: usage: pwd\n"
// liste de define plutot que decrire en brut

# define PWD			"PWD"
# define OLDPWD			"OLDPWD"
# define PATH			"PATH"
# define SHLVL			"SHLVL"
# define HOME			"HOME"
# define USER			"USER"
# define ENV_DEFAULT	"_/usr/bin/env"

// liste de define de message derreur

# define ERR_CMD "Message derreur par defaut de la commande\n"
# define SIGQUIT_MESSAGE "Quit (core dumped)\n"
# define AND_SO_ON "...."

// heredoc defines

#define HEREDOC_PATH_BASE_NAME "/tmp/.heredoc_"
#define RANDOM_NAME_LENGHT 10

typedef enum e_quote // delete ? peut etre besoin pour le parsing
{
	NONE_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote;

typedef enum e_redirect_error
{
	REDIR_SUCCESS,
	REDIR_UNEXPECTED_NEWLINE,
	REDIR_UNEXPECTED_TOKEN,
	REDIR_MISSING_FILENAME,
	REDIR_FILE_ERROR,
	REDIR_HEREDOC_EOF,
	REDIR_SYNTAX_ERROR,
}	t_redirect_error;

typedef enum e_node_type
{
	// NODE_ROOT,		// noeud racine, -> ajout une struct root dans t_ast ?
	// NODE_ARGUMENT,	// argument de commande
	NODE_OR,		// ||
	NODE_AND,		// &&
	NODE_COMMAND,	// commande simple
	NODE_PIPE,		// |
	NODE_REDIR_OUT, // >
	NODE_REDIR_IN,	// <
	NODE_APPEND,	// >>
	NODE_HEREDOC,	// <<
	NODE_BUILTIN,
	// NODE_OPEN_PAR,	// (
	// NODE_CLOSE_PAR,	// )
}	t_node_type;

typedef struct s_cmd
{
	char	*path;
	char	**cmds;
}	t_cmd;

typedef struct s_ast
{
	t_node_type		type; // type de noeud definis par lenum
	t_cmd			*cmd; // ce qu'on recupere du parsing -> remplacer par t_cmd ?
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*root; // top priority node
}	t_ast; // pas sur du nom, a discuter (t_node, t_ast_node, t_node_ast...)

typedef struct s_exec
{
	pid_t	pipe_fd[2];
}	t_exec;

typedef struct	s_token
{
	char		*content;
	bool		to_expand;
	struct s_token	*next;
}	t_token;

typedef struct s_path_cmds
{
	char	*path;
	char	**paths;
	char	*path_env;
}	t_path_cmds;

typedef struct s_minishell
{
	char	*input;
	int		exit_status;
	pid_t	pid;
	pid_t	pipe_fd[2];
	int		fd_in;
	int		fd_out;
	t_list	*envp; // liste chainee de l'environnement
	t_list	*token; // liste chainee des parametres
	t_ast	*ast_node; // Abstract Syntax Tree
}	t_minishell;

t_list	*env_init(char **envp);
t_list	*find_env_node(t_list *env, const char *var_searched);

t_ast	*create_ast_node(t_node_type type, char *content);
t_ast	*create_test_tree(void);
void	free_ast(t_ast *node);
void	print_ast(t_ast *node, int depth);

t_list	*add_node(t_list **env, char *content); // ????????
void	add_node_test(t_list *args); // ??????? oui je sais
void	free_list(t_list *list);
void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);

void	signal_handler(int signum);
// void	signal_handler_exec(int signum);

bool	replace_token(t_list *current, t_list *new_tokens);
void	free_env(t_minishell *minishell);



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

/**
 * @brief Determines if the current shell is nested within another shell.
 *
 * This function checks the "SHLVL" environment variable in the environment
 * list.
 * If the value of SHLVL is greater than 1, it indicates that a shell has been
 * launched within another shell.
 *
 * @param env_list The environment list.
 * @return 1 if the shell is nested (SHLVL > 1), 0 otherwise.
 */
int		nested_shell(t_list *env_list);







/*	----------- parsing ----------------------------------------------------- */

/**
 * @brief Tokenizes the input string into a linked list of tokens.
 *
 * This function iterates through the input string and splits it into
 * tokens separated
 * by spaces. For each token encountered, it calls extract_token() to
 * obtain the token string.
 * If extraction fails at any point, the function frees the already
 * allocated list and returns NULL.
 *
 * @param input The input string to tokenize.
 * @return A pointer to the head of a linked list containing the tokens, or NULL
 * on failure.
 */
t_list	*tokenize_input(char *input);

/**
 * @brief Checks the input string for unclosed quotes.
 *
 * This function scans the input string and uses the is_quote() helper to
 * detect opening
 * quote characters (either single or double quotes). For each opening quote
 * found, it
 * searches for a matching closing quote. If a closing quote is not found before
 * the end
 * of the string, the function prints a syntax error message to STDERR using the
 * QUOTES_S format (with the unclosed quote character) and returns 0.
 *
 * @param input The input string to be checked for unclosed quotes.
 * @return 1 if all quotes are properly closed, 0 if an unclosed quote is
 * detected.
 */
int		check_unclosed_quotes(char *input);

/**
 * @brief Checks if a character is a quote.
 *
 * This function returns a non-zero value if the given character is either a
 * single quote (')
 * or a double quote (").
 *
 * @param c The character to check.
 * @return Non-zero if c is a quote, 0 otherwise.
 */
int		is_quote(char c); //

/**
 * @brief Extracts a token from the input string.
 *
 * This function calculates the length of a token (considering quotes)
 * starting at the
 * current position in the input string. It allocates a temporary buffer,
 * copies the token
 * without quotes into it, and then duplicates the result into a final
 * dynamically allocated string.
 * The position pointer is updated to reflect the number of characters
 * processed.
 *
 * @param input The input string containing the token.
 * @param pos Pointer to the starting position in the input string;
 * updated after extraction.
 * @return A newly allocated string containing the extracted token,
 * or NULL on failure.
 */
char	*extract_token(char *input, size_t *pos);

/**
 * @brief Clears a linked list of tokens.
 *
 * This function iterates through the linked list of tokens,
 * freeing the memory
 * associated with each node's content and the node itself.
 * The next pointer of the
 * first node is reset to NULL before processing the rest of the list.
 *
 * @param token Pointer to the head of the token lipidst.
 */
void	clear_token_list(t_list *token);

/**
 * @brief Computes the length of a word in the input string, accounting for
 * quoted segments.
 *
 * Starting from the given start index, this function calculates the length of
 * a word.
 * A word is defined as a sequence of characters terminated by a space or tab.
 * Quoted segments
 * are processed appropriately using count_quoted_length.
 *
 * @param input The input string.
 * @param start The starting index for the word.
 * @return The length of the word.
 */
size_t	get_word_length(char *input, size_t start);

/**
 * @brief Copies characters from src to dest while preserving quotes.
 *
 * This function copies characters from the source string to the destination
 * buffer until
 * a space or a tab is encountered. When a quote is encountered, it copies the
 * entire quoted
 * segment (including the quotes) into dest. The variable pointed to by len is
 * updated with
 * the number of characters processed in src.
 *
 * @param dest The destination buffer.
 * @param src The source string.
 * @param len Pointer to a size_t variable that will receive the number of
 * characters processed.
 */
void	copy_with_quotes(char *dest, char *src, size_t *len);

t_list	*split_operators(const char *str, size_t i, size_t start);


bool	add_token_to_list(t_list **tokens, char *content);
bool	is_operator_char(char c, bool in_quotes);


char	*create_token(const char *str, size_t start, size_t len);

t_list	*handle_operator_error(t_list *tokens, const char *op);

t_redirect_error	check_operator_syntax(const char *str);

t_list	*handle_redirect_error(t_list *tokens, t_redirect_error error, \
	const char *token);

void	print_redirect_error(t_redirect_error error, const char *token);


/* ---- operator_utils */

size_t	get_operator_len(const char *str, size_t pos);

bool	is_redirection(char c);
bool	is_operator(char c, bool in_quotes);

/* ---- exec */

void	create_ast(t_minishell *minishell);
t_ast *create_parenthesis(t_list *token);
t_cmd	*add_cmd(char *content);
t_ast *create_ast_tree_node(t_node_type type, char *content);
void add_child(t_ast *parent, t_ast *child);
char	**update_cmd(char **cmds, char *content);
void ft_swap(t_ast *a, t_ast *b);
void	free_ast(t_ast *node);
void	ft_free(char **split);
int		error_handling_exec(t_minishell *minishell, char *message);

int		exec_minishell(t_ast *node, t_minishell *minishell);

int		handle_cmd(t_ast *node, t_minishell *minishell);
char	*find_exec_cmd(char **cmds, t_minishell *minishell);

int		handle_pipe(t_ast *node, t_minishell *minishell);

int		handle_redirin(t_ast *node, t_minishell *minishell);

int		handle_heredocin(t_ast *node, t_minishell *minishell);

int		handle_redirout(t_ast *node, t_minishell *minishell);

int		handle_redirappend(t_ast *node, t_minishell *minishell);

int		handle_builtin(t_ast *node, t_minishell *minishell);
int		ft_pwd(char **cmds);

int		ft_cd(char **cmds, t_list *envp);
int		update_cd_env(t_list **envp, char *path, int to_home);

int		ft_export(char **cmds, t_list **env);
t_list	*copy_env(t_list *env);
int		check_export(char **cmds);
int		add_export_to_env(char *cmds, t_list **env);
int		add_or_append_env(char *content, t_list **env, int len);
int		find_env_var_node(char *var, t_list **env);

int	ft_unset(char **cmds, t_minishell *minishell);
int remove_node(t_list **head, char *var);

int	ft_echo(char **cmds, t_minishell *minishell);

int	ft_exit(char **cmds, t_minishell *minishell);

char	**ft_free_double(char **strs);
char	*ft_strndup(const char *s, size_t len);
int		ft_strnlen(char *str, char c);
void swap_data(t_list *a, t_list *b);
int	ascii_cmp(char *a, char *b);
void	ft_list_sort(t_list **begin_list, int (*cmp)(char *, char *));
void	swap_strs(char **s1, char **s2);

/* --- heredoc --- */

char	*create_temp_file(void);
char	*handle_heredoc(char *delimiter);
bool	check_expand(char *delimiter);
int		check_heredoc(t_minishell *minishell);

int	is_last_heredoc(t_list *current, t_list *last_heredoc);
int	handle_last_heredoc(t_list *current, int *error);
int	is_op(char *token);
int	write_to_heredoc(char *file_name, char *delimiter);


t_list	*find_last_heredoc(t_list *start, t_list **last_heredoc);


void	handle_regular_heredoc(t_list *current);


/* test signal */
int	return_global(void);
void	heredoc_signal_handler(int sig);
void	init_global(void);
char	*read_input(t_minishell *minishell);

#endif
