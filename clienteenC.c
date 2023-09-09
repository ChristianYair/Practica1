#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "127.0.0.1"     /* server IP */
#define puerto            12346

/* Test sequences */
char datoscliente[50] = "Hola soy el cliente";      
char datosservidor[50];                     /* receive buffer */
 
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
    int sockfd; 
    struct sockaddr_in servaddr; 
    
    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
        return -1;  
    } 
    else
    {
        printf("CLIENT: Socket successfully created..\n"); 
    }
    
    
    memset(&servaddr, 0, sizeof(servaddr));

	//Asignamos los datos para el socket del server
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS ); 
    servaddr.sin_port = htons(puerto); 
  
	//Realizamos la conexion ya no es neceario el bind
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("Error en la conexion con el servidor...\n");  
        return -1;
    } 
    
    printf("Conectado...\n"); 
  
   //Leemos los mensajes
    while(1){
    
    write(sockfd, datoscliente, sizeof(datoscliente));     
    memset(datoscliente,0,50);
    memset(datosservidor,0,50);
    read(sockfd, datosservidor, sizeof(datosservidor));
    printf("CLIENT:Received: %s \n", datosservidor);
    scanf("%s",datoscliente);
    
    
    }
   
       
    /* close the socket */
    close(sockfd); 
} 
