#include "minishell.h"

t_cmds     *split_pipes(char *str)
{
    t_cmds  *list;
    t_cmds  *head;
    char    **tab;
    int     i;

    i = 0;
   tab = split_minishell(str, ';');
    if (!(list = malloc(sizeof(t_list))))
        return (NULL);
    list->entry = tab[i];
    list->pipes = split_minishell(list->entry, '|');
    head = list;

    int j = -1;
    printf("entry = %s\n", list->entry);
    while (list->pipes[++j])
        printf("pipe %d = %s\n", j, list->pipes[j]);
    

    while (tab[++i])
        {
            if (!(list->next = malloc(sizeof(t_list))))
                return (NULL);
            list = list->next;
            list->entry = tab[i];
            list->pipes = split_minishell(list->entry, '|');

            j = -1;
            printf("entry = %s\n", list->entry);
            while (list->pipes[++j])
                printf("pipe %d = %s\n", j, list->pipes[j]);

        }
    list->next = 0;
    return (head);
}