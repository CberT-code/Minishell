
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef	struct	s_redir
{
    char    **r_extern;
    char    **r_intern;
    int     **type_extern;
    int     **type_intern
	
}				t_redir;

#endif



                redir_extern [0] = "test_1", "test_2"
                redir_extern [1] =  "test_1"
                type_extern [0] = 1, 2
                type_extern [1] = 2
                nb_redir[0] = 2
                nb_redir[1] = 1