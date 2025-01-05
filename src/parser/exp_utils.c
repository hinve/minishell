#include "minishell.h"

int	is_there_a_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' || str[i] == '-' || str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char *get_env_value(const char *var, t_env *env) {
    t_env *current = env;

    while (current) {
        if (strncmp(current->key, var, strlen(var)) == 0 && current->key[strlen(var)] == '\0') {
            return current->value;
        }
        current = current->next;
    }
    return "";
}

char *replace_dollar(char *str, t_shell *data) {
    char *result = malloc(1024);
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] == '$') {
            char var_name[256];
            int k = 0;

            i++;
            if (str[i] == '\0' || str[i] == ' ' || str[i] == '$') {
                result[j++] = '$';
                continue;
            }

            while (str[i] != '\0' && (isalnum(str[i]) || str[i] == '_')) {
                var_name[k++] = str[i++];
            }
            var_name[k] = '\0';

            char *value = get_env_value(var_name, data->env);
            if (value) {
                int l = 0;
                while (value[l] != '\0') {
                    result[j++] = value[l++];
                }
            }
        } else {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
    return result;
}
