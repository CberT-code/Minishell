#ifndef MINISHELL_H
# define MINISHELL_H

typedef	struct	           s_redir
{
    char                   *str;
}			               t_redir;

#endif

void test(t_redir *redir)
{
    printf("here we test -> |%s|\n", redir->str );
    redir->str = "titi";
    printf("here we test -> |%s|\n", redir->str);
}

int main(int argc, char **str)
{
    t_redir *redir;
    
    redir = malloc(sizeof(t_redir));
    redir->str = "toto";
    test(redir);
    printf("%s\n", redir->str);
}