int         display_export_env(t_env *env, int fd)
{
    t_env   *start;

    start = env;
    if (env != NULL)
        ft_tri_varlst(&env);
    while(env != NULL)
    {
        if (env->var[ft_strlen(env->var) - 1] == '=')
        {
            write(fd, env->var, ft_strlen(env->var));
            if (env->valeur != NULL)
                write(fd, env->valeur, ft_strlen(env->valeur));
            write(fd, "\n", 1);
        }
        env = env->next;
    }
    env = start;
    return (1);
}

int         ft_env(t_args *args, t_env **env, int fd)
{
    if (args == NULL)
        return (display_export_env(*env, fd));
    return (1);
}