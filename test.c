#include "minishell.h"

int main(int argc, char **str)
{
   int i;

    i = strncmp("toto=", "toto", 5);
         printf("here we test -> %d\n", i);
}