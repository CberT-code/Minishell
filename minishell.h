<<<<<<< HEAD

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
# define MINISHELL_H

typedef	struct	s_redir
{
    char    **r_extern;
    char    **r_intern;
    int     **type_extern;
    int     **type_intern;
	
}               t_redir;

=======
#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

typedef	struct	        s_redir
{
    char                **r_extern;
    char                **r_intern;
    int                 **type_extern;
    int                 **type_intern;
}			            t_redir;

typedef struct         s_cmds
{
    char               *entry;
    char               **pipes;
    struct s_cmds      *next; 
    t_redir            redir;
}                      t_cmds;

t_cmds      *split_pipes(char *str);
char	    **ft_split_minishell(char const *s, char c);
>>>>>>> dev
#endif