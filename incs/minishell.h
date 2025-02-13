#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define RESET		"\033[0m"
# define PURPLE		"\033[0;35m"

// memo error code 127 -> no path to command
// liste de define derreurs + dautres plus tard

# define QUOTES_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define CMD_NOT_FOUND "bash: %s: command not found\n"
# define FILE_NOT_FOUND "%s: %s: No such file or directory\n"

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

typedef enum e_quote
{
	NONE_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote;

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
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type; // type noeud definis par lenum
	char			*content; // ce qu'on recupere du parsing
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*root; // top priority node
}	t_ast; // pas sur du nom, a discuté (t_node, t_ast_node, t_node_ast...)

typedef struct s_minishell
{
	char	*input;
	t_list	*envp; // liste chainee de l'environnement
	t_list	*token; // liste chainee des parametres
	t_ast	*ast_node; // Abstract Syntax Tree
}	t_minishell;

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

t_list	*env_init(char **envp);
t_list	*find_env_node(t_list *env, const char *var_searched);

t_ast	*create_ast_node(t_node_type type, char *content);
t_ast	*create_test_tree(void);
void	free_ast(t_ast *node);
void	print_ast(t_ast *node, int depth);

void	add_node(t_list **env, char *content); // ????????
void	add_node_test(t_list *args); // ??????? oui je sais
void	free_list(t_list *list);
void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp);

/**
 * @brief Checks if standard input and output are attached to a TTY.
 *
 * This function verifies that both STDIN and STDOUT are associated with a
 * terminal device.
 * If either is not a TTY (for example, when the shell is executed in a
 * non-interactive context like a pipeline),
 * an error message is printed to STDERR and the program exits successfully.
 *
 * @note The function uses dprintf to output the error message; consider
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
 * @param token Pointer to the head of the token list.
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
void	copy_with_quotes(char *dest, char *src, size_t *len); //

/**
 * @brief Updates the length counter for a quoted segment in the input string.
 *
 * Starting at the specified start index in the input string, this function
 * increments the length
 * counter (pointed to by i) to skip over a quoted segment. If the quote is a
 * single quote or a
 * double quote containing an environment variable, the quotes are taken
 * into account.
 *
 * @param input The input string.
 * @param i Pointer to the length counter to be updated.
 * @param start The starting index of the quoted segment.
 */
void	handle_quotes_len(char *input, size_t *i, size_t start);

/**
 * @brief Advances the index past a quoted segment in the input string.
 *
 * This static helper function increments the index (pointed to by i) so that
 * it skips over
 * a quoted segment, including the opening and closing quotes.
 *
 * @param input The input string.
 * @param i Pointer to the index; updated to point past the quoted segment.
 */
void	count_quoted_length(char *input, size_t *i);

/**
 * @brief Checks if the substring of str starting at index i contains an
 * environment variable.
 *
 * This function scans the string starting from index i until a quote is
 * encountered. If a '$'
 * character is found, it indicates the presence of an environment variable.
 *
 * @param str The input string.
 * @param i The starting index.
 * @return 1 if an environment variable is detected, 0 otherwise.
 */
int		has_env_variable(char *str, size_t i);

#endif
