
#include "minishell.h"


int recognize_var(char *cmd)
{
    if (strchr(cmd, '=') != NULL)
    {
        printf("Setting variable: %s\n", cmd);
        return 1; // Variable to set
    }

    if (strncmp(cmd, "$", 1) == 0)
    {
        printf("Referencing variable: %s\n", cmd);
        return 2; // Variable to reference
    }

    printf("Not a variable command: %s\n", cmd);
    return 0; // Not a variable command
}

int is_cmd_in_varname(t_cmd *cmd, t_var *var_list)
{
    t_var *current = var_list;

    while (current)
    {
        if (strcmp(cmd->arg[0], current->varname) == 0)
        {
            return 1; // Found a match
        }
        current = current->next;
    }
    return 0;
}

void print_variable(t_var *var, char *key)
{
    t_var *current = var;

    while (current != NULL)
    {
        if (strcmp(current->varname, key) == 0)
        {
            printf("%s\n", current->value);
            return;
        }
        current = current->next;
    }
    printf("Variable '%s' not found\n", key);
}
 
t_var *create_var_node(char *input)
{
    t_var *new_var = (t_var *)malloc(sizeof(t_var));
    int i = 0;

    while (input[i] != '=')
        i++;
    new_var->varname = ft_substr(input, 0, i);
    if (!new_var)
    {
        perror("malloc");
        return NULL;
    }
    new_var->value = ft_substr(input, i + 1, strlen(input) - i - 1);
    new_var->next = NULL;
    return new_var;
}

void add_var(t_var *var, t_cmd cmd)
{
    t_var *new_var = create_var_node(cmd.arg[0]);


    if (!new_var)
        return;

    if (var == NULL)
    {
        new_var->next = var;
    }
    else
    {
        t_var *current = var;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_var;
    }
}