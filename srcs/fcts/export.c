#include "../../minishell.h"

char         *check_var(char *str)
{
    int     i;

    i = 0;
    while (str[i] == ' ' || str[i] == '\"')
        i++;
    if (str[i] != '\0')
        return (ft_strcpyuntil(str + i, " ="));
    else 
        return (NULL);
}

char         *check_value(char *str, int i)
{
    char    *ret;
    int     start;

    if (str[i] == '\"' || str[i] == '\'')
        i++;
    start = i;
    if (ft_in_quotes(str, i) != 0)
    {
        while (ft_in_quotes(str, i) != 0)
            i++;
        i -= start;
        i--;
        ret = ft_strncpy(str + start, i);
        return (ret);
    }
    if (str[i] != ' ')
        return (ft_strcpyuntil(str + i, " "));
    return (NULL);
}

int        replace_env(t_env **env, char *var, char *value)
{
    t_env   *env_n;

    env_n = *env;
    while (*env != NULL)
    {
        if (ft_strcmp((*env)->var, var) == 0)
        {
            (*env)->valeur = value;
            *env = env_n;
            return (1);
        }
        *env = (*env)->next;
    }
    *env = env_n;
    return (0);
}

void        add_env(t_env **env, t_env **data)
{
     t_env   *env_n;
     t_env   *start;
     int    find;

    start = *data;
    env_n = *env;
    while (*data != NULL)
    {
        find = 0;
         while ((*env)->next != NULL && find == 0)
        {
            if (ft_strcmp((*data)->var, (*env)->var) == 0)
            {
                find = 1;
            }
            *env = (*env)->next;
        }
        if (find == 0 && (*data)->valeur != NULL)
            ft_lstadd_back_env(env, (*data)->var, (*data)->valeur);
        *data = (*data)->next;
    }
    *data = start;
    *env = env_n;
}

void        suppr_maillon(t_env **list, t_env *ptr)
{
    t_env   *start;

    start = *list;
    if (*list == NULL)
    {
        *list = (*list)->next;
        return ;
    }
    while (*list != NULL)
    {
        if ((*list)->next == ptr)
        {
            (*list)->next = ptr->next;
            free(ptr);
            *list = start;
            return ;
        }
        *list = (*list)->next;
    }
    *list = start;
}

void        clean_data(t_env **data)
{
    t_env   *start;

    start = NULL;
    while (*data != NULL)
    {
        if ((*data)->valeur != NULL)
            suppr_maillon(&start, *data);
        else
            if (start == NULL)
                start = *data;
         *data = (*data)->next;
    }
    *data = start;
}

void        clean_env(t_env **env)
{
    t_env   *start;

    start = NULL;
    while (*env != NULL)
    {
        if ((*env)->valeur == NULL)
            suppr_maillon(&start, *env);
        else
            if (start == NULL)
                start = *env;
         *env = (*env)->next;
    }
    *env = start;
}

int         ft_export(char *str, t_env **env, int fd)
{
    if (ft_strcmp(str, "export") == 0)
        return (display_export(*env, fd));
    data_list(str + 6, env);
    //add_env(env, data);
    // clean_data(data);
    // clean_env(env);
    return (1);
}
