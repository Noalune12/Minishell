#include "minishell.h"

bool	check_expand(char *delimiter)
{
	size_t	i;

	i = 0;
	while (delimiter[i])
	{
		if (is_quote(delimiter[i]))
			return (false);
		i++;
	}
	return (true);
}

// gestion heredoc -> expand tout le temps,
// peu importe le format (si il y a des quotes ou non)
// ouvrir tous les heredoc,  peu importe le check de syntaxe des operateurs

// gestion expand:
// cat << EOF && export test="TEST" && cat << OEF ---> avec $test
// dans les heredocs
// remplacement de << EOF par -> "<< filename"
// si identification de "<<" (heredoc), le parametre delimiteur sera
// remplacé par le filename, et doit expand -> check expand pendant le parsing?
