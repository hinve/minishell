# include "minishell.h"

void expand_variables(t_token **token, t_shell *data) {
    t_token *aux = *token;

    while (aux) {
        if (aux->type == HEREDOC) {
            aux = aux->next;
        } else {
            if (is_there_a_dollar(aux->content) && 
                (aux->type == DQUOTE || aux->type == WORD)) {
                char *new_content = replace_dollar(aux->content, data);
                free(aux->content); // Libera la memoria previa
                aux->content = ft_strdup(new_content); // Duplica el contenido nuevo
                free(new_content); // Libera la cadena temporal
            }
            aux = aux->next;
        }
    }
}