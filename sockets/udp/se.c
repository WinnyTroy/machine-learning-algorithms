//P15/31457/2015
//KIRAGU WINNIE WANGECHI
//Server socket(udp implementation of sockets.)

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 50


int display(float mat[MAX][MAX], int rows, int columns);
int determinant(float mat[MAX][MAX], int n);
void getcofac(float mat[MAX][MAX],float temp[MAX][MAX], int p, int q, int n);

float mat[MAX][MAX];
int n;

int main(){
  int serv_sock;
  struct sockaddr_in serv_addr;
  socklen_t addr_size;
  int i;

  /*Create UDP socket*/
  serv_sock = socket(AF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7777);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);  

  /*Bind socket with address struct*/
  if(bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Binding failed");
  }

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serv_addr;

  //loop for receiving and sending result determinant
  while(1){
    printf("\nWaiting for client...\n\n");
    fflush(stdout);

    if(recvfrom(serv_sock,&n,sizeof(n),0,(struct sockaddr *)&serv_addr, &addr_size)<0)
    {
      printf("\n----Error receiving matrix order!----\n");
    }else{
      printf("---Order received: %d\n\n",n);
      if(recvfrom(serv_sock,&mat,sizeof(mat),0,(struct sockaddr *)&serv_addr, &addr_size)<0)
      {
        printf("\n----Error receiving matrix!----\n");
      }else{
        printf("---Matrix received:\n\n");
        display(mat,n,n);

        //find determinant
        float det = determinant(mat,n);
        printf("The determinant sent is %.2f\n",det);
        if(sendto(serv_sock,&det,sizeof(det),0,(struct sockaddr *)&serv_addr,addr_size)<0)
        {
          printf("\n----Error sending determinant!----");
        }
      }
    }
  }


  return 0;
}

int determinant(float mat[MAX][MAX], int n){
  int i,j,k,sign = 1;

  //calculate determinant
  float det = 0;

  if(n == 1) //if 1 by 1 matrix 
  {
    return mat[0][0] ;
  }

  float temp[MAX][MAX];
  for(k = 0; k < n; k++) // cofactor of each element on first row
  {
    getcofac(mat,temp, 0, k, n);
    det += sign * (mat[0][k] * determinant(temp, n-1));
    sign = -sign;
  }

  return det;
}

void getcofac(float mat[MAX][MAX],float temp[MAX][MAX], int row, int col, int n){
  int i = 0, j = 0,k,l;

  //copy elements into temp 
  for(k = 0; k < n; k++)
  {
    for(l = 0; l < n; l++)
    {
      if(k != row && l != col)
      {
        temp[i][j++] = mat[k][l];
        if(j == n - 1 )
        {
          j = 0;  //reset col index
          i++;  //increase rol index
        }
      }
    }
  }
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
