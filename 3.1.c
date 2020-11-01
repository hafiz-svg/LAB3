#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int main(void)
{

  void signal_handler(int sig);
  char s[200];

  if (signal(SIGINT, signal_handler) || signal(SIGQUIT,signal_handler) || signal(SIGTSTP,signal_handler) == SIG_ERR)
{
     perror("signal");
     exit(1);
  }

  printf("Enter a string:\n");

  if (fgets(s, 200, stdin) == NULL)
      perror("gets");
  else
      printf("you entered: %s\n", s);

  return 0;
}

void signal_handler(int sig)
{
  char *str=malloc(50);
if(sig==2)
{
str="SIGINT";
}
else if(sig==3)
{
str="SIGQUIT";
}
else
{
str="SIGTSTP";
}
printf("\tThis is a special signal handler for %s\n",str);
}

