#include "minishell.h"

int	is_there_a_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' || str[i] == '-' || str[i] == '~')
			return (1);
	return (0);
}
