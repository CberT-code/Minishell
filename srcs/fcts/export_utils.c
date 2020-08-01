#include "../../minishell.h"

int         display_export(t_env *env, int fd)
{
    t_env   *start;

    start = env;
        if (env != NULL)
        ft_tri_varlst(&env);
    while(env != NULL)
    {
        write(fd, "declare -x ", 11);
        write(fd, env->var, ft_strlen(env->var));
        if (env->valeur != NULL)
        {
            write(fd, "\"", 1);
            write(fd, env->valeur, ft_strlen(env->valeur));
            write(fd, "\"", 1);
        }
        if (env->valeur == NULL && env->var[ft_strlen(env->var)] == '=')
            write(fd, "\"\"", 2);
        write(fd, "\n", 1);
        env = env->next;
    }
    env = start;
    return (1);
}

int    ft_tablen(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return (i);
    while (tab[i])
        i++;
    return (i);
}

char        *double_char(char *str, char c)
{
    int i;
    char *ret;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == c && str[i + 1] != c && (str[i - 1] != c || i == 0))
        {
            ret = add_char(str, c, i);
            free(str);
            str = ret; 
        }
        i++;
    }
    return (str);
}

char        **ft_tri_vartab(char **tab)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (tab[i])
    {
        j = 0;
        while (j < ft_tablen(tab) - 1)
        {
            if (ft_strcmp(tab[j], tab[j + 1]) > 0)
            {
                temp = ft_strdup(tab[j]);
                tab[j] = ft_strdup(tab[j + 1]);
                tab[j + 1] = ft_strdup(temp);
            }
            j++;
        }
        i++;
    }
    return (tab);
}

void         data_list(char *str, t_env **data, t_env **env)
{
    int     i;
    char    *var;
    char    *value;

    i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\"' || str[i] == '\'')
         i++;
        var = check_var(str + i);
        i += ft_strlen(var);
        if (str[--i] == '=' && var != NULL)
        {
            value = check_value(str, ++i);
            if (str[i] == '\"')
                i += 2;
            i += ft_strlen(value);
            replace_env(data, var, value);
            if (replace_env(env, var, value) == 0)
                ft_lstadd_back_env(env, var, value);
        }
        else
        {
            value = NULL;
            replace_env(env, var, NULL);
            if (replace_env(data, var, NULL) == 0)
               ft_lstadd_back_env(data, var, value);
            i++;
        }
    }
}    
