#include stdio.h
#include sys/types.h
#include sys/socket.h
#include netinet.h


int main(int argc, char const *argv[])
{
	// declaration of variables to be used in the programme
	int sockdfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in server_addr cli_addr;
	int n;

	if (argc < 2)
	{
		printf("Error, no port provided\n");
		exit(1);
	}


	// create the socket
	sockdfd = socket(AF_NET, SOCK_STREAM, 0);

	if (sockdfd < 0)
	{
		printf("Error opening socket\n");
		exit(1);
	}

	// bzero method is used to clear the complete structure(the server address) before
	// using the server address
	bzero((char* ) &server_addr, sizeof(server_addr) );

	// first we store the port no, then fill in the other required details
	// atoi() function in C language converts string data type to int data type. 
	// The htons() function makes sure that numbers are stored in memory are converted from integer format to network byte order.
	portno = atoi(argv[1]);
	server_addr.sin_family = AF_NET;
	server_addr.sin_addr.sin_addr = INADDR_ANY;
	server_addr.sin_port = htons(portno)

	if (bind(sockdfd, ( struct *) & server_addr), sizeof(server_addr) < 0)
	{
		printf("Error in binding\n");
	}

	listen(sockdfd, 5)
}
