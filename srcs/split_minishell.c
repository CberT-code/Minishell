/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:52:35 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/20 14:44:42 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			split_semicol(char *str, t_semicol *semicol, char **env)
{
    int start;
    start = 0;
    if (!str)
        return (0);
    str = ft_clean_spaces(str);
    printf("here we test -> |%s|\n", str);
    //str = ft_envcpy(str, env);
    //printf("here we test -> |%s|\n", str);
    while (*str)
    {
        lstadd_back_semicol(&semicol, ft_substr(str, start, ft_strlen_str_quotes(str, ";")));
        str += ft_strlen_str_quotes(str, ";");
        if (*str == ';')
            str++;
    }
    return (1);
}

t_pipes			*split_pipes(char *str)
{
    t_pipes     *pipes;

    if (!str)
        return (NULL);
    pipes = NULL;
    while (*str)
    {
        lstadd_back_pipes(&pipes, ft_substr(str, 0, ft_strlen_str_quotes(str, "|")));
        str += ft_strlen_str_quotes(str, "|");
        if (*str == '|')
            str++;
    }
    return (pipes);
}

t_args          *split_args(char *str)
{
    t_args     *args;

    if (!str || *str == '\0')
        return (NULL);
    args = NULL;
    while (*str)
    {
        lstadd_back_args(&args, ft_substr(str, 0, ft_strlen_str_quotes(str, " ")));
        str += ft_strlen_str_quotes(str, " ");
        if (*str == ' ')
        str++;
    }
    return (args);
}

t_cmds			cmds_args(char *str)
{
    t_cmds      cmd;

    while (*str == ' ')
        str++;
    cmd.str = ft_substr(str, 0, ft_strlen_str_quotes(str, " "));
    printf("\t\tcmd -> |%s|%d\n", cmd.str, ft_strlen_str_quotes(str, " "));
    str += ft_strlen_str_quotes(str, " ") + 1;
    cmd.args = split_args(str);
    return (cmd); 
}

int		main(int argc, char **argv, char **env)
{
	char *str;
	int		fd;
    t_semicol   *semicol;

	str = NULL;
    semicol = NULL;
	fd = 0;
	get_next_line(fd, &str);
	close(fd);
    split_semicol(str, semicol, env);
	return (0);
}