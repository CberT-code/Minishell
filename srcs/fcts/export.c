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

void        replace_env(t_env *env, t_env *data)
{
    t_env   *data_n;

     while (env->next != NULL)
    {
        data_n = data;
         while (data_n != NULL)
        {
            if (ft_strcmp(data_n->var, env->var) == 0)
                env->valeur = data_n->valeur;
            data_n = data_n->next;
        }
        env = env->next;
    }
}

void        add_env(t_env *env, t_env *data)
{
     t_env   *env_n;
     int    find;

     while (data != NULL)
    {
        env_n = env;
        find = 0;
         while (env_n->next != NULL && find == 0)
        {
            if (ft_strcmp(data->var, env_n->var) == 0)
             find = 1;
            env_n = env->next;
        }
        if (find == 0)
            ft_lstadd_back_env(&env, data->var, data->valeur);
        data = data->next;
    }
}
                                                 
int         ft_export(char *str, t_env **env, t_env **data, int fd)
{
    if (ft_strcmp(str, "export") == 0)
    {
        display_export(*env, fd);
        return (display_export(*data, fd));
    }
    data_list(str + 6, data, env);
    //add_env(env, data);
    // while ((*data) != NULL)
    // {
    //      *data = (*data)->next;
    //      printf("%s%s\n", (*data)->var, (*data)->valeur);
    // }
    return (1);
}
