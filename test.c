#include "minishell.h"

void	test(t_tab_redir *redir)
{
	printf("here we test -> %p\n", redir);
}

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

   str2 = "echo titi";

	printf("here we test -> |%s|\n", ft_substr(str2, 0, 4));
	str2 += 6;
	printf("here we test -> |%s|\n", ft_substr(str2, 0, 4));
   
   
}