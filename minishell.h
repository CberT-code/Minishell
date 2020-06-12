
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

#endif