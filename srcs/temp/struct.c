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
		return ;
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
