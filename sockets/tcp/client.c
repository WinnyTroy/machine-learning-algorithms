//P15/31457/2015
//KIRAGU WINNIE WANGECHI
//Client socket(tcp implementation of sockets.)


// Compiled and run as below
// gcc client.c -o client.out  
// ./client.out


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 50 

int display(float mat[MAX][MAX], int rows, int columns); //prints matrix

float mat[MAX][MAX],det;
int n;

int main(){
  int client_sock,new_sock,flag = 0;
  struct sockaddr_in serv_addr;
  socklen_t addr_size;

  //create socket
  client_sock = socket(AF_INET, SOCK_STREAM, 0);
  
  //server address settings
  serv_addr.sin_family = AF_INET;//Address family = Internet
  serv_addr.sin_port = htons(7777);//port number
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.12");// IP address 

  //connect to server socket using address
  addr_size = sizeof serv_addr;
  if((new_sock=connect(client_sock, (struct sockaddr *) &serv_addr, addr_size))<0)
	{
		printf("Failed to connect...\n\n");
	}else{
    printf("Connection Successful!...\n\n");
    
    //user input
    printf("Please input square matrix order(integer!):\n");
    if( scanf("%d", &n) != 1)//validate integer
    {
      printf("Invalid Value for Matrix order!\n");
      flag = 1;
      goto End;
    }else{
      if(n <= 0 || n > MAX) //validate matrix size
      {
        printf("Invalid matrix size!(1-50)\n");
        flag = 1;
        goto End;   
      }

      for(int i = 0; i < n; i++)
      {
        for(int j = 0; j < n; j++)
        {
          printf("[%d][%d] = ",i,j);
          if( scanf("%f",&mat[i][j]) != 1)//validate integer
          {
            printf("Invalid Value!\n");
            flag = 1;
            goto End;
          }
        }
      }
      //send validation flag
      End:
      write(client_sock,&flag,sizeof(flag));
      if(flag == 1)
      {
        return 0;
      }
      printf("\nMatrix:\n");
      display(mat,n,n);

      //send matrix to server socket
      write(client_sock,&n,sizeof(n));
      write(client_sock,mat,sizeof(mat));
      printf("\nMatrix sent!\n");

      //recieve determinant
      if(read(client_sock,&det,sizeof(det))<0) 
      {
        printf("Determinant not received!\n\n"); 
      }else{
        printf("Determinant is %.2f\n",det);
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

