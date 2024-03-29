#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>		// inet_ntoa
#include <time.h> 			// time

int error( int ern, const char *msg ){
    perror( msg );
    return ern;
}

int main() {
	printf("asdf");
	/* zmienne predefiniowane *****************************************/
	int  port   = 12345;
	
	/* zmienne niezainicjowane ****************************************/
	int 		n;		
	int 		fd, newfd;
	char 		buffer[256];
	socklen_t 	socklen;
	
	struct 	sockaddr_in serv_addr, cli_addr;
	
	/* tworzymy gniazdo ***********************************************/
	fd = socket( AF_INET, SOCK_STREAM, 0 );		// tworzymy nowe gniazdo
	if (fd < 0) 
        return error( 1, "socket()" );
        
    /* zapelniamy strukture zerami (inicjujemy) ***********************/
	bzero( ( char * ) &serv_addr, sizeof( serv_addr ) );	// zapelniamy strukture zerami
	
	/* przypisujemy parametry *****************************************/
	serv_addr.sin_family 	  	= AF_INET;			// typ gniazda 
	serv_addr.sin_addr.s_addr 	= INADDR_ANY;		// oczekujemy polaczen na kazdym adresie
	serv_addr.sin_port 			= htons(port);		// port, na ktorym nasluchujemy
	
	/* mapujemy gniazdo ***********************************************/
	if( bind(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) 
		return error( 2, "bind()" );
	
	/* rozpoczynamy nasluchiwanie na gniezdzie ************************/
	listen( fd, 5 );
	
	/* kod obslugujacy nowe polaczenia ********************************/
	socklen = sizeof(cli_addr);
	
	// while( ( newfd = accept( fd, (struct sockaddr *) &cli_addr, &socklen ) ) ){
	// 	/* sprawdzamy, czy udalo sie nawiazac polaczenie **************/
	// 	if( newfd < 0 ){	// jesli wystapil blad, to wyswietlamy o nim informacje
	// 		perror( "accept()" );
	// 	}else{					// a jesli bledu nie bylo...
	// 		/* wypisujemy informacje o polaczeniu *********************/
	// 		printf("Address: %s Port: %d\n",  inet_ntoa( cli_addr.sin_addr ), cli_addr.sin_port );
			  
	// 		/* przekazujemy klientowi informacje o biezacym czasie ****/
	// 		bzero( buffer, 256 );
	// 		sprintf( buffer, "Current time: %d", (int) time( NULL ) );
	// 		n = write( newfd, buffer, sizeof( buffer ) );
	// 		if( n < 0 ) 	// sprawdzamy, czy wystapil blad ....
	// 			perror( "write()" );

	// 		/* konczymy polaczenie ************************************/
	// 		close(newfd);
	// 	}
	// }
	// zamknięcie gniazda
	close(fd);
	
		printf("end");
	return 0; 
}