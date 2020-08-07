#include "minishell.h"


// int main(int argc, char **str)
// {
//    t_pipes *pipe;

//    pipe = NULL;
//    pipe = malloc(sizeof(t_pipes) + 1);
//    ft_bzero(pipe, sizeof(t_pipes));
//    printf("here we test -> %p\n", &pipe->redir_in);
//    test(&pipe->redir_in);
// }
int main(int argc, char **str)
{
	char *str2;
	struct stat	buf;

	printf("here we test -> %d\n", stat("/home/user42/Minishell2/Minishell", &buf));
   
   
}