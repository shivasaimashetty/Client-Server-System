#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define MAX_SIZE 1024

void serviceClient(int);

int main(int argc, char *argv[]){  
  int sd, client, portNumber, status;
  struct sockaddr_in servAdd;      // client socket address
 
 if(argc != 2){
    printf("Call model: %s <Port Number>\n", argv[0]);
    exit(0);
  }
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "Cannot create socket\n");
    exit(1);
  }
  sd = socket(AF_INET, SOCK_STREAM, 0);
  servAdd.sin_family = AF_INET;
  servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);
 
  bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
  listen(sd, 5);

  while(1){
    printf("Waiting for a client to chat with\n");
    client = accept(sd, NULL, NULL);
    printf("Got a client, start chatting\n");
 
    if(!fork())
      serviceClient(client);

    close(client);
    waitpid(0, &status, WNOHANG);
  }
}

void serviceClient(int sd)
{
char buf[255];
int m,n, pid,size,status;
char *t,*c;
char d[40],*com[40],*a[40];
write(sd, "start chatting", 16);
pid=fork();
if(!pid)
{
	while(1)
	{
		int count=0;
		if(n=read(sd, buf, 255))
		{
	     		buf[n]='\0';
			fprintf(stderr,"%s",buf);
			c=strdup(buf);
			t=strtok(buf,";&|\n");
			while(t!=NULL)
			{
				d[count]=c[t - buf + strlen(t)];
				com[count]=t;
				count++;
				t=strtok(NULL,";&|\n");
			}
			com[count]=NULL;
			status=-1;
			for(int k=0;k<count;k++)
			{
				//printf("%s\n",temp[k]);
				if(status > -1)
				{
					if(d[k-1]=='&')
					{
						if(status!=0)
							break;
					}
					else if(d[k-1]=='|')
					{
						if(status==0)
							break;
					}
				}


				t=strtok(com[k]," ");
				int tot=0;
				while(t!=NULL)
				{
					a[tot]=t;
					//printf("%s\n",commands[total]);
					tot++;
					t=strtok(NULL," ");
				}
				a[tot]=NULL;
				if(strcmp(a[0],"exit") == 0)
					exit(0);
				int pid1 = fork();
				if(!pid1)
				{
					dup2(sd,1);
					execvp(a[0],a);
					fprintf(stderr,"execvp() System call has failed\n");
					exit(1);
				}
				else
				{
					m=wait(&status);
				//	if(WIFEXITED(status))
				//		printf("Child %d exited with status %d\n",pid1,WEXITSTATUS(status));
				}

			}
		}
	}

}	 

if(pid)
 /*sending messages to the client */
	while(1)

		if(n=read(0, buf, 255))
		{
			buf[n]='\0';
			write(sd, buf, strlen(buf)+1);
		}

}
