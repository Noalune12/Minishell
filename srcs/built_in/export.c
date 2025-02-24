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

char	*copy_dquotes(char *content)
{
	char	*content_dquotes;
	size_t	i;
	size_t	j;
	bool	equal;

	equal = false;
	content_dquotes = ft_calloc((ft_strlen(content) + 3), sizeof(char));
	if (!content_dquotes)
		return (NULL);
	i = 0;
	j = 0;
	while (content[i])
	{
		content_dquotes[j] = content[i];
		if (content[i] == '=' && equal == false)
		{
			content_dquotes[++j] = '\"';
			equal = true;
		}
		j++;
		i++;
	}
	if (equal == true)
		content_dquotes[j] = '\"';
	return (content_dquotes);
}

t_list	*copy_env(t_list *env)
{
	t_list	*new_list;
	t_list	*temp;
	char	*content_dquotes;

	new_list = NULL;
	temp = env;
	while (temp)
	{
		add_node(&new_list, temp->content);
		temp = temp->next;
	}
	temp = new_list;
	while (temp)
	{
		content_dquotes = copy_dquotes(temp->content);
		if (!content_dquotes)
		{
			free_list(new_list);
			return (NULL);
		}
		free(temp->content);
		temp->content = content_dquotes;
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
	if (!sorted)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		return ;
	}
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

int	ft_export(char **cmds, t_list **env)
{
	int		i;
	int		ret = 0;

	i = 0;

	if (!cmds[++i])
	{
		ft_print_export(*env);
		return (ret);
	}
	else
		ret = check_export(cmds);
	while (cmds[i])
	{
		add_export_to_env(cmds[i], env);
		i++;
	}
	return (ret);
}
