#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <math.h>

int main (void)
{
void sigint_hadler(int sig);
int fd[2];
pipe(fd);
pid_t pid=fork();
int no;

if(signal(SIGINT,sigint_hadler)==SIG_ERR)
{
perror("signal");
exit(1);
}
if(pid>0)
{
wait(NULL);
close(0);
close(fd[1]);
dup(fd[0]);
read(fd[0],&no,sizeof(no));
int i,flag=0;

for (i=2;i<=no/2;i++)
{
if(no%i==0)
{
flag=1;
break;
}
}

if(no==1)
{
printf("1 is neither prime or composite.");
}
else
{
if(flag==0)
printf("%d is a prime number.\n",no);
else
printf("%d is not a prime number.\n",no);
}
}
else if(pid==0)
{
printf("Enter number: \n");
scanf("%d",&no);
close(1);
close(fd[0]);
dup(fd[1]);
write(fd[1],&no,sizeof(no));
exit(EXIT_SUCCESS);
}
return EXIT_SUCCESS;
}
void sigint_hadler(int sig)
{
printf("SIGINT handler!\n");
}
