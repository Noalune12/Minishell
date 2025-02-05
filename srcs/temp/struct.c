#include "minishell.h"

void create_struct(t_args *args)
{
	args->arg = NULL;
	args->token = 0;
	args->next = NULL;
}

void add_node(t_args *args)
{
	t_args *temp;
	t_args *new_node;

	if (!args)
		return;

	new_node = malloc(sizeof(t_args));
	if (!new_node)
		return;
	create_struct(new_node);

	if (!args->next)
	{
		args->next = new_node;
		return;
	}

	temp = args->next;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void free_struct(t_args *args)
{
	t_args *current;
	t_args *next;

	if (!args->next)
		return;

	current = args->next;
	while (current)
	{
		next = current->next;
		if (current->arg)
			free(current->arg);
		free(current);
		current = next;
	}
	args->next = NULL;
}

// void	free_struct(t_args *args)
// {
// 	t_args	*tmp;

// 	if (!args)
// 		return ;
// 	while (args->next)
// 	{
// 		tmp = args->next;
// 		if (args->next)
// 			free_struct(args);
// 		if (args)
// 			free(args);
// 	}
// }


// t_parse	*create_node(t_parse *parsing)
// {
// 	parsing = malloc(sizeof(t_parse));
// 	if (!parsing)
// 		return (NULL);
// 	parsing->t_type = 0;
// 	parsing->content = NULL;
// 	parsing->next = NULL;
// 	return (parsing);
// }

// void	parse_add_back(t_parse *parsing)
// {
// 	t_parse	*node;
// 	t_parse	*tmp;

// 	tmp = parsing;
// 	node = create_node(node);
// }
