#include  "minishell.h"

int ascii_cmp(const char *a, const char *b)
{
	return (strcmp(a, b));
}

void swap_data(t_list *a, t_list *b)
{
	char *temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void ft_list_sort(t_list **begin_list, int (*cmp)(const char *, const char *))
{
	t_list *list;
	t_list *next;
	int swap;

	if (!begin_list || !cmp)
		return ;
	swap = 1;
	while (swap) {
		swap = 0;
		list = *begin_list;
		while (list->next) {
			next = list->next;
			if (cmp(list->content, next->content) > 0)
			{
				swap_data(list, next);
				swap = 1;
			}
			list = list->next;
		}
	}
}

t_list	*copy_env(t_list *env)
{
	t_list	*new_list;
	t_list	*temp;

	new_list = NULL;
	temp = env;
	while (temp)
	{
		add_node(&new_list, temp->content);
		temp = temp->next;
	}
	return (new_list);
}

void	free_env_export(t_list *env)
{
	t_list	*temp;

	if (!env)
		return;
	temp = env;
	while (temp)
	{
		temp = env->next;
		if (env->content)
			free(env->content);
		free(env);
		env = temp;
	}
}

void	ft_print_export(t_list *env)
{
	t_list	*sorted;
	t_list	*temp;

	sorted = copy_env(env);
	ft_list_sort(&sorted, &ascii_cmp);
	temp = sorted;
	while (temp)
	{
		printf("export ");
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	free_env_export(sorted);
}

//should begin with _ or letter -> check what it takes
//if between quote can take space

void	ft_export(char **cmds, t_list **env)
{
	int		i;
	int		len;
	int		equal;
	char	*content;

	i = 0;
	len = 0;
	equal = 0;
	if (!cmds[++i])
	{
		ft_print_export(*env);
		return ;
	}
	// while(input[i] && input[i] != ' ')
	// {
	// 	if (input[i] == '=')
	// 		equal = 1;
	// 	i++;
	// 	len++;
	// }
	// if (equal == 1)
	// {
	// 	content = ft_strndup(input + i - len, len);
	// 	add_node(env, content);
	// 	free(content);
	// }
}
