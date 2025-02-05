#include "minishell.h"

#define MAX_LENGTH 1024

//''e''c'ho 'b''o"nj"o"'u'r" -> handle when quote take space too here ==> "echo "

// check double or single quote left open --> bash: error: one quote is left open
// count nb of sep
//skip spaces
// if no sep and no \0 only one arg
// check if builtin with strncmp
// if $ find var in env and replace be careful with quote

void	check_quotes(const char *input, bool *in_s_quote, bool *in_d_quote)
{
	int	i;

	i = 0;
	if (input[i] == '\'' && !(*in_d_quote))
	{
		if (*in_s_quote)
			*in_s_quote = FALSE; // out of single quotes
		else
			*in_s_quote = TRUE;  // enter single quotes
	}
	else if (input[i] == '\"' && !(*in_s_quote))
	{
		if (*in_d_quote)
			*in_d_quote = FALSE; // out of double quotes
		else
			*in_d_quote = TRUE;  // enter doubel quotes
	}
}

bool	check_quotes_closed(const char *input)
{
	int		i;
	bool	in_s_quote;
	bool	in_d_quote;

	in_s_quote = FALSE;
	in_d_quote = FALSE;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '\'' && !in_d_quote) || (input[i] == '\"' && !in_s_quote))
			check_quotes(&input[i], &in_s_quote, &in_d_quote);
		i++;
	}
	if (in_s_quote || in_d_quote)
		return (FALSE);
	return (TRUE);
}

bool	precheck_input(const char *input, int *i)
{
	if (!check_quotes_closed(input))
	{
		printf("bash: error: one quote is left opened\n"); // how to handle echo $?
		return (FALSE);
	}
	printf(YELLOW"quotes are closed\n"RESET);
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\v'))
		(*i)++;
	if (!input[*i])
	{
		printf(YELLOW"only space or tab\n"RESET); // echo $? return value of previous cmd
		return (FALSE);
	}
	return (TRUE);
}

bool	parse_input(const char *input, t_args *args)
{

	(void) args; // erreur de compilation avec -Werror
	int	i;

	i = 0;
	if (!precheck_input(input, &i))
		return (FALSE);
	return (TRUE);
}

char	*ft_reallocate(char *str, char c, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
	{
		if (len > 1)
			free(str);
		printf("Malloc failed");
		return (NULL);
	}
	while (len > 1 && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	if (len > 1)
		free(str);
	return (ret);
}

char	*handle_quotes(char *input)
{
	char	*result;
	int		len;
	bool	in_s_quote;
	bool	in_d_quote;

	result = NULL;
	len = 0;
	in_s_quote = false;
	in_d_quote = false;
	while ((*input))
	{
		if ((*input == '\'' && !in_d_quote) || (*input == '\"' && !in_s_quote))
			check_quotes(*input, &in_s_quote, &in_d_quote);
		// if we are not in quotes, or in double quotes, or in single quotes
		else if ((in_s_quote && !in_d_quote) || (in_d_quote && !in_s_quote)
			|| (!in_s_quote && !in_d_quote))
		{
			len++;
			result = ft_reallocate(result, *input, len);
			if (!result)
				return (NULL);
		}
		input++;
	}
	return (result);
}
