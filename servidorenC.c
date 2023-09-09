#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <errno.h>

#define server_addr "127.0.0.1"
#define puerto 12346

int main()
{

	int fd,longcliente,mensajer;
	
	//Declaracion del mensaje
	char datos[50], datosen[50]={"Bienvenido"};
	
	
	
	struct sockaddr_in servaddr = {0};
	struct sockaddr_in clientaddr= {0};
	
	//Configuracion del servidor
	servaddr.sin_family = AF_INET;//tcp/ip
	servaddr.sin_port = htons(puerto);
	servaddr.sin_addr.s_addr = inet_addr(server_addr);
	
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}
	
	
	//Creacion del socket
	int rc = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(rc!=0){
		fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n",errno,strerror(errno));
		return -1;
	}
		
	//Modo escucha
	if(listen(sockfd,5)==-1){
		printf("Error en listen()\n");
		exit(-1);
	}
	printf("\nEscuchando en el puerto %d...\n",puerto);
	
	//Aceptar conexiones
	while(1){
		
		longcliente=sizeof(clientaddr);
		//Aceptamos 
		if((fd=accept(sockfd,(struct sockaddr *)&clientaddr,&longcliente))==-1){
			printf("Error en acept()\n");
			exit(-1);
		}
		printf("Cliente encontrado\n");
		


		//Recibimos los datos
		while(1){
		
		
		send(fd,datosen,sizeof(datosen),0);
		memset(datos,0,50);
		memset(datosen,0,50);
		mensajer=read(fd, datos, sizeof(datos));
		printf("El mensaje es %s\n", datos);
		scanf("%s",datosen);
		
		}

	}
	
	
	close(fd);	
	close(sockfd);
	
    return 0;
}
