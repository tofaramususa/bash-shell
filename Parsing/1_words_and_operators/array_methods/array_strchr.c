

#include "arrays.h"

bool	array_strchr(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (true);
		i++;
	}
	if ((char) c == '\0')
		return (true);
	return (false);
}