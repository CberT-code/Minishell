#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  int status;
  int i;

  char *cat_args[] = {"cat", "pipes.c", NULL};
  char *grep_args[] = {"grep", "cat", NULL};
  char *cut_args[] = {"cut", "-b", "1-10", NULL};

  int pipes[4];
  pipe(pipes);
  pipe(pipes + 2);
  
  if (fork() == 0)
    {
      dup2(pipes[1], 1);

      close(pipes[0]);
      close(pipes[1]);
      close(pipes[2]);
      close(pipes[3]);

      execvp(*cat_args, cat_args);
    }
  else
    {

      if (fork() == 0)
	{
	  
	  dup2(pipes[0], 0);

	  dup2(pipes[3], 1);

	  close(pipes[0]);
	  close(pipes[1]);
	  close(pipes[2]);
	  close(pipes[3]);

	  execvp(*grep_args, grep_args);
	}
      else
	{

	  if (fork() == 0)
	    {

	      dup2(pipes[2], 0);

	      close(pipes[0]);
	      close(pipes[1]);
	      close(pipes[2]);
	      close(pipes[3]);

	     if (execvp(*cut_args, cut_args))
            exit;
	    }
	}
    }
  
  close(pipes[0]);
  close(pipes[1]);
  close(pipes[2]);
  close(pipes[3]);

  for (i = 0; i < 3; i++)
    wait(&status);
}