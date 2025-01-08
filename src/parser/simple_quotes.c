# include "minishell.h"

void remove_quotes_and_spaces(char **cmd) {
    char *equal_pos = strstr(*cmd, "=");
    if (equal_pos) {
        if (*(equal_pos + 1) == '\'') {
            char *closing_quote = strchr(equal_pos + 2, '\'');
            if (closing_quote) {
                size_t prefix_len = equal_pos - *cmd + 1;
                size_t content_len = closing_quote - (equal_pos + 2);
                size_t suffix_len = strlen(closing_quote + 1);
                char *new_cmd = malloc(prefix_len + content_len + suffix_len + 1);
                if (!new_cmd) {
                    printf("Error: memoria insuficiente\n");
                    exit(1);
                }
                strncpy(new_cmd, *cmd, prefix_len);
                new_cmd[prefix_len] = '\0';
                strncat(new_cmd, equal_pos + 2, content_len);
                strcat(new_cmd, closing_quote + 1);
                free(*cmd);
                *cmd = new_cmd;
            }
        }
    }
}