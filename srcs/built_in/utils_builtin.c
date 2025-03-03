#include "minishell.h"

char	*ft_strndup(const char *s, size_t len)
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

int	ft_strnlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	ascii_cmp(char *a, char *b)
{
	return (ft_strcmp(a, b));
}

void	swap_data(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)(char *,
	char *))
{
	t_list	*list;
	t_list	*next;
	bool	swap;

	if (!begin_list || !cmp)
		return ;
	swap = true;
	while (swap)
	{
		swap = false;
		list = *begin_list;
		while (list->next)
		{
			next = list->next;
			if (cmp(list->content, next->content) > 0)
			{
				swap_data(list, next);
				swap = true;
			}
			list = list->next;
		}
	}
}
