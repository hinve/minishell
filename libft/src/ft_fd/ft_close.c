#include "libft.h"

void    free_tab(char **tab)
{
    int i = 0;
    if (tab == NULL)
    {
        return;
    }
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}