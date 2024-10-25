#include "minishell.h"

int	quote_stuff(int *i, char *str_cmd)
{
	int	quote_count;

	quote_count = 0;
	while (str_cmd[*i])
	{
		*i += 1;
		if (str_cmd[*i] == '\'')
			return (quote_count);
		else if (str_cmd[*i + 1] == '\0')
			return (-1);
		quote_count++;
	}
	return (0);
}

int	dquote_stuff(int *i, char *str_cmd)
{
	int	quote_count;

	quote_count = 0;
	while (str_cmd[*i])
	{
		*i += 1;
		if (str_cmd[*i] == '"')
			return (quote_count);
		else if (str_cmd[*i + 1] == '\0')
			return (-1);
		quote_count++;
	}
	return (0);
}

int quote_count(char *str) {
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i]) {
		if (str[i] == '"' || str[i] == '\'') {
			count++;
		}
		i++;
	}
	return count;
}
