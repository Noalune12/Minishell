#include "libft.h"
#include "exec.h"

static int	fill_new_cmds(char **cmds, int *index, char **new_cmd, char **ret)
{
	int		i;
	int		k;
	int		j;

	i = -1;
	while (++i < *index)
		ret[i] = cmds[i];
	j = -1;
	while (new_cmd[++j])
	{
		ret[*index] = new_cmd[j];
		(*index)++;
	}
	k = *index;
	i++;
	while (cmds[i])
	{
		ret[k] = cmds[i];
		i++;
		k++;
	}
	ret[k] = NULL;
	return (0);
}

char	**remake_cmds(char **cmds, int *index)
{
	char	**new_cmd;
	int		cmds_len;
	int		new_cmd_len;
	char	**ret;

	cmds_len = 0;
	new_cmd_len = 0;
	new_cmd = ft_split(cmds[*index], ' '); // TODO protect
	if (new_cmd == NULL)
		return (NULL);
	while (cmds[cmds_len])
		cmds_len++;
	while (new_cmd[new_cmd_len])
		new_cmd_len++;
	ret = malloc((cmds_len + new_cmd_len) * sizeof(char *)); // TODO protect
	if (ret == NULL)
	{
		free(new_cmd);
		return (NULL);
	}
	fill_new_cmds(cmds, index, new_cmd, ret);
	(*index)--;
	free(cmds);
	free(new_cmd);
	return (ret);
}
