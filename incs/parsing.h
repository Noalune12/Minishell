#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_token			t_token;
typedef struct s_list			t_list;
typedef enum e_redirect_error	t_redirect_error;

typedef struct s_tokenizer
{
	size_t	i;
	size_t	start;
	bool	in_quotes;
	char	quote_type;
	char	*str;
}	t_tokenizer;


void	handle_quotes(char c, bool *in_quotes, char *quote_type);

/**
 * @brief Computes the length of a word in the input string, accounting for
 * quoted segments.
 *
 * Starting from the given start index, this function calculates the length of
 * a word.
 * A word is defined as a sequence of characters terminated by a space or tab.
 *
 * @param input The input string.
 * @param start The starting index for the word.
 * @return The length of the word.
 */
size_t	get_word_length(char *input, size_t start);

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
int	is_quote(char c);

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
// t_list	*tokenize_input(char *input);

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





t_redirect_error	check_operator_syntax(const char *str);

t_list	*handle_redirect_error(t_list *tokens, t_redirect_error error, \
	const char *token);


size_t	get_operator_len(const char *str, size_t pos);

bool	is_redirection(char c);
bool	is_operator(char c, bool in_quotes);

#endif
