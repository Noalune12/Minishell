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

# define QUOTES_SYNTAX_ERROR "minishell: syntax error near unexpected token `%s'\n"
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
void	tty_check(void);
void	update_pwd(t_list **env);
void	update_shlvl(t_list *env);

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
 * @brief Verifies that all quotes in the input string are properly closed.
 *
 * This function iterates over the input string and, for every
 * opening quote encountered,
 * searches for the corresponding closing quote. If an opening quote
 * is not closed,
 * an error message is printed to STDERR and the function returns 0.
 *
 * @param input The input string to check.
 * @return 1 if all quotes are properly closed, 0 otherwise.
 */
int		check_quote(char *input);

/**
 * @brief Checks the input string for unclosed quotes.
 *
 * This function scans the input string and uses the is_quote() helper to detect opening
 * quote characters (either single or double quotes). For each opening quote found, it
 * searches for a matching closing quote. If a closing quote is not found before the end
 * of the string, the function prints a syntax error message to STDERR using the
 * QUOTES_SYNTAX_ERROR format (with the unclosed quote character) and returns 0.
 *
 * @param input The input string to be checked for unclosed quotes.
 * @return 1 if all quotes are properly closed, 0 if an unclosed quote is detected.
 */
int	check_unclosed_quotes(char *input);

/**
 * @brief Checks if a character is a quote.
 *
 * This function tests whether the provided character is either a single
 * quote (') or a double quote (").
 *
 * @param c The character to test.
 * @return A non-zero value if c is a quote, 0 otherwise.
 */
int		is_quote(char c);

/**
 * @brief Checks a token for quote-related syntax errors.
 *
 * This function iterates over the characters in the provided token
 * until a space is encountered.
 * It uses the helper function is_quote() to detect quote characters.
 * While processing the command
 * part (i.e., before the first space), if a quote character is found,
 * the function prints a syntax
 * error message (using the QUOTES_SYNTAX_ERROR format) to STDERR and
 * returns 0, indicating a syntax error.
 * If no such error is found, the function returns 1.
 *
 * @param token The token string to be checked for syntax errors.
 * @return 1 if no syntax error is found, 0 if a syntax error
 * (improper use of quotes) is detected.
 */
int	check_syntax_error(char *token);

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
 * @brief Extracts the token content enclosed by quotes from the input string.
 *
 * This function assumes that the token starts with a quote character at the
 * current
 * position indicated by *i. It extracts all characters until it finds the
 * matching
 * closing quote and returns the resulting substring (excluding the quotes).
 * The index
 * pointer *i is updated to point to the character immediately after
 * the closing quote.
 *
 * @param input The input string containing the token.
 * @param i Pointer to the current index in the input string;
 * updated after extraction.
 * @return A newly allocated string with the token content (without the quotes),
 * or NULL on failure.
 */
char	*get_token_content(char *input, size_t *i);

/**
 * @brief Extracts unquoted content from the input string.
 *
 * Starting from the index pointed to by *i in the input string, this function
 * extracts a substring
 * until a quote or a space is encountered. The extracted substring (allocated
 * dynamically) is returned,
 * and *i is updated to point immediately after the extracted content.
 *
 * @param input The input string from which to extract content.
 * @param i Pointer to the current index in the input string;
 * updated after extraction.
 * @return A newly allocated string containing the unquoted content,
 * or NULL on failure.
 */
char	*get_unquoted_content(char *input, size_t *i);

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
 * @brief Copies the source string to the destination while removing quotes.
 *
 * This function iterates over the source string until it encounters a space.
 * If a quoted sequence
 * is detected, the content inside the quotes is copied (without the quotes)
 * into the destination.
 * The parameter pointed to by len is updated with the number of characters
 * processed in the source.
 *
 * @param dst The destination buffer where the unquoted string will be copied.
 * @param src The source string to copy.
 * @param len Pointer to a size_t variable that will be set to the number of
 * characters processed in src.
 */
void	copy_without_quotes(char *dest, char *src, size_t *len);

/**
 * @brief Calculates the length of a word in the input string, taking quotes
 * into account.
 *
 * This function starts at the given index in the input string and returns the
 * number of characters that
 * compose a "word". A word is defined as a sequence of characters terminated
 * by a space.
 * If quotes are encountered, the content between the quotes is considered part
 * of the same word.
 *
 * @param input The input string.
 * @param start The starting index in the input string.
 * @return The length of the word starting at the given index.
 */
size_t	get_word_length(char *input, size_t start);

#endif
