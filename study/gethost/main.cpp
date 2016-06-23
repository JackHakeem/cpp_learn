
#include <stdio.h>
#include <netdb.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

using std::string;

int main(int argc, char* argv[])

{
	struct sockaddr_in addr;
	if ( 0 != inet_aton (argv[1], &addr.sin_addr) )
		printf("%s no need to gethostbyname\n", argv[1]);
	
	struct hostent* host;
	host = ::gethostbyname(argv[1]);
	
	if ( host )
	{	
		string s = inet_ntoa( *( (struct in_addr*)host->h_addr ) );
		printf("dns host of %s is %s\n", argv[1], s.c_str());

	}

	return 0;

}


