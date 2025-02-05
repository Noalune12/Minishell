#include "minishell.h"

t_args	*create_struct(t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args)
		return NULL;
	args->arg = NULL;
	args->token = 0;
	args->next = NULL;
	return (args);
}

void	add_node(t_args **args)
{
	t_args	*temp;
	t_args	*new_node;

	if (!args || !(*args))
		return ; //bool ?
	temp = *args;
	new_node = create_struct(*args);
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	free_struct(t_args *args)
{
	t_args	*temp;

	if (!args)
		return ;
	temp = args;
	while (temp)
	{
		if (temp->arg)
			free(temp->arg);
		temp = args->next;
		free(args);
		args = temp;
	}
}
