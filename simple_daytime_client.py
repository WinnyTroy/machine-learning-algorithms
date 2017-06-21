

// an implementation of a TCP time-of-day client.
// This client establishes a TCP connection with a server and the server simply sends back the
// current time and date in a human-readable format.



// Include our own header.
// It includes several different headers that  are needed by most network
// programs and defines various constant that we use.
# include "unp.h"
int main(int argc, char ** argv) 
{
        int sockfd, n
        char recvline[MAXLINE + 1]
        struct sockaddr_in servaddr

        if (argc != 2)
        err_quit("usage: a.out <IPaddress>")


    // creating an internet stream socket(TCP SOCKET)
    // socket() returns a small integer descriptor that we can use to identify the socket
    // in all future function calls
        if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
        	err_sys("socket error");

        // We fill in an Internet socket address structure with the server IP address and port number
        // set the address family to AF_INET, set the port number to 13
        bzero( servaddr, servaddr.sin_family= AF_INET;
                servaddr.sin_port=htons(13) / * daytime server * /


        if(inet_pton(AF_INET, argv[1], & servaddr.sin_addr) <= 0)
			err_quit("inet_pton error for %s", argv[1])

		// Establish a connection with the server
		if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
			err_sys("connect error")

		// Read and display the server's reply

		while ((n=read(sockfd, recvline, MAXLINE)) > 0) {
    		recvline[n]=0

    		if (fputs(recvline, stdout) == EOF)
   				err_sys("fputs error")
		}
		if (n < 0)
    		err_sys("read error")
    	// Terminate the program
    	exit(0)
    	}