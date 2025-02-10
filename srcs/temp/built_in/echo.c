#include "../../../incs/minishell.h"

/*
COLOR CODE :
- YELLOW = debug message
- PURPLE = print terminal
- RED = error
*/

void	get_echo_info(char *input, int *i, int *no_nl)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	if (!input[*i])
		printf(YELLOW"echo has no agument\n"RESET);
	if (input[*i] && input[*i + 1] && strncmp(input + *i, "-n", 2) == 0) // check if flag -n
	{
		if (!input[*i + 2] || (input[*i + 2] && input[*i + 2] == ' '))
		{
			*no_nl = 1;
			printf(YELLOW"no nl\n"RESET);
			*i += 2;
		}
	}
	while (input[*i]) // /!\ only -n no print
	{
		if (input[*i] == ' '
			&& (input[*i + 1] && input[*i + 2] && strncmp(input + *i + 1, "-n", 2) == 0)
			&& (!input[*i + 3] || (input[*i + 3] && input[*i + 3] == ' ')))
			*i += 3;
		else
			break ;
	}
}

char	*find_var_env(char *var, t_list *env, int len)
{
	int		i;
	t_list	*temp;
	char	*content;

	i = 0;
	temp = env;
	content = NULL;
	if (!(temp->content))
		return (NULL);
	while (temp)
	{
		if (strncmp(temp->content, var, len) == 0)
			{
				content = temp->content + len + 1;
				break ;
			}
		temp = temp->next;
	}
	return (content);
}

char	*ft_strndup(const char *s, size_t len) // utils
{
	char		*str;
	size_t		i;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	print_var(char *input, t_list *env, int *i)
{
	char	*var;
	char	*content;
	size_t	len;
	size_t	j;

	var = NULL;
	len = 0;
	j = *i + 1;
	if (!input[*i + 1])
		return ;
	else
		(*i)++;
	while (input[j] && input[j] != '$' && input[j] != ' ')
	{
		len++;
		j++;
	}
	var = ft_strndup(input + *i, len); //protect ?
	content = find_var_env(var, env, len); // handle in parsing ??
	if (content)
		printf("%s", content);
	(*i) += len - 1;
	free(var);
}

void	ft_print_echo(char *input, t_list *env)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			while (input[i + 1] && input[i + 1] == ' ') // handle in parsing rm extra space
			i++;
		}
		if (input[i] != '$')
			printf(PURPLE"%c"RESET, input[i]);
		else
			print_var(input, env, &i);
		i++;
	}
}
void	ft_echo(char *input, t_list *env) // if pipe after write in pipe + adapt with struct
{
	int no_nl = 0;
	int i = 4;

	if (input[i] && input[i] != ' ')
	{
		printf(RED"bash: %s: command not found\n"RESET, input);
		return ;
	}
	get_echo_info(input, &i, &no_nl);
	if (no_nl && !input[i])
		printf(YELLOW"echo -n has no agument\n"RESET);
	while (input[i] && input[i] == ' ')
		i++;
	ft_print_echo(input + i, env);
	if (!no_nl)
		printf("\n");
}
