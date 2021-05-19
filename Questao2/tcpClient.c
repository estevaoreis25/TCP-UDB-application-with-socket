#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE    	100

void tratasinal(int s){
	if(s == SIGINT){
		printf(" --> Digite FIM para encerrar conexão!!!\n>");
	}
}

int main(int argc,char * argv[]) {

	struct  sockaddr_in data_server; // contem os dados do server	
	int     sd;          	      // descritor              
	int     n,k;                  // caracteres lidos do server
	char    buf_sen[MAX_SIZE];     // buffer de dados enviados  
	char    buf_rec[MAX_SIZE];     // buffer de dados recebidos  
	signal(SIGINT,  tratasinal);
	// confere o numero de argumentos passados para o programa 
  	if(argc<3)  {
    	   printf("uso correto: %s <ip_do_servidor> <porta_do_servidor>\n", argv[0]);
    	   exit(1);  }

	memset((char *)&data_server,0,sizeof(data_server)); // limpa estrutura 
	memset((char *)&buf_sen,0,sizeof(buf_sen));     // limpa o buffer 
	
	data_server.sin_family      = AF_INET; // configura o socket a internet
	data_server.sin_addr.s_addr = inet_addr(argv[1]);
	data_server.sin_port        = htons(atoi(argv[2]));

	// Cria socket
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "Criacao do socket falhou!\n");
		exit(1); }

	// Conecta socket ao servidor definido 
	if (connect(sd, (struct sockaddr *)&data_server, sizeof(data_server)) < 0) {
		fprintf(stderr,"Tentativa de conexao falhou!\n");
		exit(1); }
	while (1) {
		printf("> ");
		fgets(buf_sen, MAX_SIZE, stdin);    // le dados do teclado 
		send(sd,&buf_sen,strlen(buf_sen),0); // envia dados  
		if (strncmp(buf_sen, "FIM",3) == 0) // Se a mensagem enviada for igual a FIM, o cliente encerra
			break;							// a conexão com o servidor
		if(strcmp(buf_sen, "LIBERADO\n") == 0){ // Se a mensagem que o cliente enviou for igual a LIBERADO,
												// irá receber dados do servidor
		do{

			if ((n = recv(sd, buf_rec, 8192, 0)) > 0) { // recebendo dados da função send do servidor
	        buf_rec[n] = '\0'; // define fim da string

	        fprintf(stdout, "Servidor >> %s\n", buf_rec); // Printa mensagem recebida do servidor
	   		}
   		}while(strcmp (buf_rec, "LIBERADO") != 0 ); // Envia dados enquanto for diferente de LIBERADO
   	}

	} // fim while 
	printf("------- conexão com o servidor encerrada -----\n");
	close (sd); // fecha o socket
	return (0);
} // fim do programa 

