#include "libft.h"

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
