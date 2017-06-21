//P15/31457/2015
//KIRAGU WINNIE WANGECHI
//Client socket(udp implementation of sockets.)

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 50

//prototypes
int display(float mat[MAX][MAX], int rows, int columns);

float mat[MAX][MAX],det;//matrix for user input
int n;

int main(){
  int client_sock, portNum;
  struct sockaddr_in serv_addr;
  socklen_t addr_size;

  /*Create UDP socket*/
  client_sock = socket(AF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7777);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serv_addr;

  while(1){
    //ask for user input
    printf("\n\nPlease input square matrix order:\n");
    
    if( scanf("%d", &n) != 1)//validate integer
    {
      printf("Invalid Value!\n");
      return 0;
    }else{
      int i,j;

      for(i = 0; i < n; i++)
      {
        for(j = 0; j < n; j++)
        {
          printf("[%d][%d] = ",i,j);
          if( scanf("%f",&mat[i][j]) != 1)//validate integer
          {
            printf("Invalid Value!\n");
            return 0;
          }
        }
      }

      printf("\nMatrix:\n");
      display(mat,n,n);

      //send matrix to server socket
      if(sendto(client_sock,&n,sizeof(n),0,(struct sockaddr *)&serv_addr,addr_size)<0)
      {
        printf("---The order of the matrix [%d] was not sent!---\n",n);
      }else{
        printf("---Order sent!\n\n");
        if(sendto(client_sock,&mat,sizeof(mat),0,(struct sockaddr *)&serv_addr,addr_size)<0)
        {
          printf("---The matrix was not sent!---\n",n);
        }else{
          printf("---Matrix sent!\n\n");
          if(recvfrom(client_sock,&det,sizeof(det),0,(struct sockaddr *)&serv_addr, &addr_size)<0)
          {
            printf("\n----Error receiving determinant!----\n");
          }else{
            printf("---The determinant received is: %.2f\n\n",det);
          }
        }
      }
    }
  }

  return 0;
}

int display(float mat[MAX][MAX], int rows, int columns)
{
  int i,j;
  for(i = 0; i < rows; i++)
  {
    for(j = 0; j < columns; j++)
    {
      printf("%.2f ",mat[i][j]);
    }
    printf("\n");
  }
  printf("_________________________________\n");
}
