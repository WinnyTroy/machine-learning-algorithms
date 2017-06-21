//P15/31457/2015
//KIRAGU WINNIE WANGECHI
//Server socket(tcp implementation of sockets.)

// Compiled and run as below
// gcc server.c -o main.out  
// ./main.out


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 50

int display(float mat[MAX][MAX], int rows, int columns);
int determinant(float mat[MAX][MAX], int n);
void getcofac(float mat[MAX][MAX],float temp[MAX][MAX], int p, int q, int n);

float mat[MAX][MAX];
int n;

int main(){

  int server_sock, new_sock, flag;
  struct sockaddr_in serv_addr;	
  socklen_t addr_size;

  //create socket
  if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
   printf("Error creating socket\n"); 	
  }
  else{
    printf("Socket successfully created\n\n");


	// memset method is used to clear the complete structure(the server address) before
	// using the server address
    memset(&serv_addr, '0', sizeof(serv_addr));

    //server address settings
    serv_addr.sin_family = AF_INET;//Address family = Internet
    serv_addr.sin_port = htons(7777);//port number
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//localhost IP address
    
    //bind the address struct to the socket
    bind(server_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    //Listen on the socket with 
    if(listen(server_sock,2)==0)
    {
      printf("Waiting...\n");
    }
    else{
      printf("Error occurred!\n");
    }
    //server always listening
    while(1)
    {
      //Accept call and create new socket for incoming connection
      addr_size = sizeof serv_addr;
      new_sock = accept(server_sock, (struct sockaddr *) &serv_addr, &addr_size);
      if(new_sock<0)
      {
        printf("Error accepting conection!\n");
      }else{
        printf("Connected to client!\n\n");
      }

      //check validation flag
      if(read(new_sock,&flag,sizeof(flag))<0)
      {
        printf("Flag not received\n\n"); 
      }else{
        if(flag == 1)
        {
          printf("Validation error!\n Transmission ended.\n");
          close(new_sock);
          continue;
        }
      } 

     //Receive matrix order from client 
      if(read(new_sock,&n,sizeof(n))<0)
      {
        printf("Matrix order    not received\n\n"); 
      }else{
     	  printf("Matrix order received:%d\n",n); 

        //Use matrix received by client to calculate determinant 
        if(read(new_sock,&mat,sizeof(mat))<0)
        {
          printf("Matrix not received\n\n"); 
        }else{
            printf("Matrix received:\n"); 
            display(mat,n,n);
            float det = determinant(mat,n);
            printf("The determinant sent is %f\n",det);
            //send determinant result back to client
            write(new_sock,&det,sizeof(det));
        } 
      }
    }
  }
	//close(new_sock);
  return 0;
}


int determinant(float mat[MAX][MAX], int n){
  int i,j,k,sign = 1;

  //calculate determinant
  float det = 0;

  if(n == 1) //if 1 by 1 matrix (base case)
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
      printf("%f ",mat[i][j]);
    }
    printf("\n");
  }
  printf("_________________________________\n");
}
