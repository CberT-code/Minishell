int     find_fcts(t_cmds *cmd, env)
{
    if (strcmp(cmd->str, "echo") == 0)
        return (ft_echo(cmd->args, env));
    if (strcmp(cmd->str, "env") == 0)
        return (ft_env(cmd->args, env));
    if (strcmp(cmd->str, "export") == 0)
        return (ft_export(cmd->args, env));
    if (strcmp(cmd->str, "cd") == 0)
        return (ft_cd(cmd->args, env));
    if (strcmp(cmd->str, "pwd") == 0)
        return (ft_pwd(cmd->args, env));
    if (strcmp(cmd->str, "unset") == 0)
        return (ft_unset(cmd->args, env));
    if (strcmp(cmd->str, "exit") == 0)
        return (ft_exit(cmd->args, env));
}